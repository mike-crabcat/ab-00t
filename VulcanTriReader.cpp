#include <cassert>
#include <cstring>
#include <memory>

#include "VulcanTriReader.h"
#include "endian.h"
#include "fastlz.h"
#include "kaitai/kaitaistruct.h"

VulcanTriReader::VulcanTriReader(const std::string path) {
  mCurrentOffset = 0;
  mCurrentPage = NULL;

  mFstream.open(path);
  if (!mFstream.is_open())
    throw std::runtime_error("Failed to open path");

  mDataStream = std::make_shared<kaitai::kstream>(&mFstream);
  mDataStruct = std::make_shared<vulcan_00t_t>(mDataStream.get());

  // init
  fetchPageIndex(0);

  seek(72);
  read(&mNumVertices, 4);
  mNumVertices = be32toh(mNumVertices);

  seek(96);
  read(&mNumTriangles, 4);
  mNumTriangles = be32toh(mNumTriangles);

  mVertices = readVerticesBuffer();
  mTriangles = readTriangleBuffer();
}

std::vector<double> VulcanTriReader::readVerticesBuffer() {
  std::vector<double> vertices(3 * mNumVertices);

  // Vertices start at this offset
  seek(72 + 24 + 24);

  char tempBuffer[8];
  char *targetBuffer = (char *) vertices.data();

  for (size_t i = 0; i < mNumVertices * 3; i++) {
    read(tempBuffer, 8);

    // Flip buffer
    targetBuffer[i * 8 + 0] = tempBuffer[7];
    targetBuffer[i * 8 + 1] = tempBuffer[6];
    targetBuffer[i * 8 + 2] = tempBuffer[5];
    targetBuffer[i * 8 + 3] = tempBuffer[4];
    targetBuffer[i * 8 + 4] = tempBuffer[3];
    targetBuffer[i * 8 + 5] = tempBuffer[2];
    targetBuffer[i * 8 + 6] = tempBuffer[1];
    targetBuffer[i * 8 + 7] = tempBuffer[0];
  }

  return vertices;
}

std::vector<int> VulcanTriReader::readTriangleBuffer() {
  std::vector<int> triangles(3 * mNumTriangles);

  // Triangles start at this offset
  seek(72 + 24 + 24 + 24 * mNumVertices);

  // Triangle index buffer is padded so that each triangle is 12 bytes of
  // data followed by 12 bytes of padding
  uint32_t tempBuffer[6];
  for (size_t i = 0; i < mNumTriangles; i++) {
    read(tempBuffer, sizeof(uint32_t) * 6);

    triangles[i * 3 + 0] = be32toh(tempBuffer[0]) - 1;
    triangles[i * 3 + 1] = be32toh(tempBuffer[1]) - 1;
    triangles[i * 3 + 2] = be32toh(tempBuffer[2]) - 1;
  }

  return triangles;
}

void VulcanTriReader::fetchPageIndex(size_t pageIndex) {
  ldiv_t l3Div = std::div((int64_t)pageIndex, (uint32_t)256);
  ldiv_t l2Div = std::div((int64_t)l3Div.quot, (uint32_t)256);
  ldiv_t l1Div = std::div((int64_t)l2Div.quot, (uint32_t)256);
  ldiv_t l0Div = std::div((int64_t)l1Div.quot, (uint32_t)256);

  if (l0Div.quot != 0)
    throw std::runtime_error("Offset too big");

  mCurrentPage = mDataStruct->root()
                     ->children()
                     ->at(l0Div.rem)
                     ->children()
                     ->at(l1Div.rem)
                     ->children()
                     ->at(l2Div.rem)
                     ->children()
                     ->at(l3Div.rem)
                     ->page();

  fastlz_decompress(mCurrentPage->compressed_data().c_str(),
                    mCurrentPage->compressed_data_size(), mCurrentPageData,
                    sizeof(mCurrentPageData));
}

void VulcanTriReader::seek(size_t offset) {

  // Within current page? just change current offset within page
  if (offset >= mCurrentPage->page_start() &&
      offset < mCurrentPage->page_end()) {
    mCurrentOffset = offset;
  }
  // Load new page based on offset
  else {
    size_t pageIndex = offset / mDataStruct->compression_block_size();
    fetchPageIndex(pageIndex);
    mCurrentOffset = offset;
  }
}

void VulcanTriReader::read(void *target, uint32_t length) {
  size_t targetOffset = 0;
  while (true) {
    size_t a = mCurrentOffset - mCurrentPage->page_start();
    size_t b = std::min<size_t>(a + length, mCurrentPage->page_end());
    std::memcpy((char *)target + targetOffset, &mCurrentPageData[a], b - a);
    targetOffset += b - a;
    length -= b - a;
    mCurrentOffset += b - a;
    if (length > 0) {
      seek(mCurrentOffset);
    } else
      break;
  }
}
