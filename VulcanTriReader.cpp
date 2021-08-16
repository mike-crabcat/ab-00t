#include <cassert>
#include <cstring>
#include <memory>

#include "VulcanTriReader.h"
#include "endian.h"
#include "fastlz.h"
#include "kaitai/kaitaistruct.h"

VulcanTriReader::VulcanTriReader(const std::string path) {

  mCurrentPageSize = 0;
  mCurrentPageStart = 0;
  mCurrentPageEnd = 0;
  mCurrentOffset = 0;

  mFstream.open(path);
  if (!mFstream.is_open())
    throw std::runtime_error("Failed to open path");

  mDataStream = std::make_shared<kaitai::kstream>(&mFstream);
  mDataStruct = std::make_shared<vulcan_00t_t>(mDataStream.get());
}

void VulcanTriReader::readHeader(int &numVertex, int &numTriangles) {
  // Read sizes
  seek(72);
  read(&numVertex, 4);
  numVertex = be32toh(numVertex);
  seek(96);
  read(&numTriangles, 4);
  numTriangles = be32toh(numTriangles);
}

bool VulcanTriReader::readVertexBuffer(double *buffer, size_t bufferSize) {
  int numVertex, numTriangles;
  readHeader(numVertex, numTriangles);

  // Vertices start at this offset
  seek(72 + 24 + 24);

  size_t readLength = sizeof(double) * 3 * numVertex;
  if (readLength != bufferSize)
    return false;

  char tempBuffer[8];
  char *targetBuffer = (char *)buffer;
  for (size_t i = 0; i < numVertex * 3; i++) {
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
  // read(buffer, sizeof(double) * 3 * numVertex);

  // //Fix endianness of buffer
  // for(size_t i=0;i<3 * numVertex;i++) {
  //     buffer[i] = (buffer[i]);
  // }

  return true;
}

bool VulcanTriReader::readTriangleBuffer(uint32_t *buffer, size_t bufferSize) {
  int numVertex, numTriangles;
  readHeader(numVertex, numTriangles);

  size_t readLength = sizeof(uint32_t) * 3 * numTriangles;
  if (readLength > bufferSize)
    return false;

  // Vertices start at this offset
  seek(72 + 24 + 24 + 24 * numVertex);

  // Triangle index buffer is padded so that each triangle is 12 bytes of data
  // followed by 12 bytes of padding
  uint32_t tempBuffer[6];
  for (size_t i = 0; i < numTriangles; i++) {
    read(tempBuffer, sizeof(uint32_t) * 6);
    buffer[i * 3 + 0] = be32toh(tempBuffer[0]);
    buffer[i * 3 + 1] = be32toh(tempBuffer[1]);
    buffer[i * 3 + 2] = be32toh(tempBuffer[2]);

    assert(buffer[i * 3 + 0] != 0);
  }

  return true;
}

void VulcanTriReader::seek(uint32_t offset) {

  // Within current page? just change current offset within page
  if (offset >= mCurrentPageStart && offset < mCurrentPageEnd) {
    mCurrentOffset = offset;
  }
  // Load new page based on offset
  else {
    uint32_t pageIndex = offset / mDataStruct->compression_block_size();
    ldiv_t l3Div = std::div((int64_t)pageIndex, (uint32_t)256);
    ldiv_t l2Div = std::div((int64_t)l3Div.quot, (uint32_t)256);
    ldiv_t l1Div = std::div((int64_t)l2Div.quot, (uint32_t)256);
    ldiv_t l0Div = std::div((int64_t)l1Div.quot, (uint32_t)256);

    if (l0Div.quot != 0)
      throw std::runtime_error("Offset too big");

    vulcan_00t_t::page_t *page = mDataStruct->root()
                                     ->children()
                                     ->at(l0Div.rem)
                                     ->children()
                                     ->at(l1Div.rem)
                                     ->children()
                                     ->at(l2Div.rem)
                                     ->children()
                                     ->at(l3Div.rem)
                                     ->page();

    // Decompress page into current page buffer
    mCurrentPageSize = fastlz_decompress(
        page->compressed_data().c_str(), page->compressed_data_size(),
        mCurrentPageData, sizeof(mCurrentPageData));

    std::cout << "Page size " << mCurrentPageSize << " from "
              << mDataStruct->compression_block_size() << std::endl;

    mCurrentOffset = offset;
    mCurrentPageStart = page->page_start();
    mCurrentPageEnd = page->page_end();
    mCurrentPageIndex = pageIndex;
  }
}

void VulcanTriReader::read(void *target, uint32_t length) {
  size_t targetOffset = 0;
  while (true) {
    uint32_t a = mCurrentOffset - mCurrentPageStart;
    uint32_t b = std::min(a + length, mCurrentPageEnd);
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
