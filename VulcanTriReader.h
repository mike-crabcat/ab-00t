#include <fstream>
#include <iostream>

#include "vulcan_00t.h"

const int VULCAN_MAX_PAGE_SIZE = 256 * 1024;

class VulcanTriReader {
public:
  VulcanTriReader(const std::string path);

  int numVertices() const { return mNumVertices; };
  int numTriangles() const { return mNumTriangles; };

  std::vector<double> const& vertices() const {
    return mVertices;
  }

  std::vector<int> const& triangles() const {
    return mTriangles;
  }

private:
  void fetchPageIndex(size_t pageIndex);
  void seek(size_t offset);
  void read(void *target, uint32_t length);

  std::vector<double> readVerticesBuffer();
  std::vector<int> readTriangleBuffer();

  std::ifstream mFstream;
  std::shared_ptr<kaitai::kstream> mDataStream;
  std::shared_ptr<vulcan_00t_t> mDataStruct;

  size_t mNumVertices;
  size_t mNumTriangles;

  std::vector<double> mVertices;
  std::vector<int> mTriangles;

  size_t mCurrentOffset;
  vulcan_00t_t::page_t *mCurrentPage;

  char mCurrentPageData[VULCAN_MAX_PAGE_SIZE];
};
