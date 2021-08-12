#include <iostream>
#include <fstream>

#include "vulcan_00t.h"

const int VULCAN_MAX_PAGE_SIZE = 256*1024;


class VulcanTriReader {
    public: 
        VulcanTriReader(const std::string path);

        void readHeader(int& numVertex, int& numTriangles);
        bool readVertexBuffer(double* buffer, size_t bufferSize);
        bool readTriangleBuffer(uint32_t* buffer, size_t bufferSize);

    private:
        void seek(uint32_t offset);
        void read(void* target, uint32_t length);
        
        std::ifstream mFstream;
        std::shared_ptr<kaitai::kstream> mDataStream;
        std::shared_ptr<vulcan_00t_t> mDataStruct;

        uint32_t mCurrentOffset;

        uint32_t mCurrentPageStart;
        uint32_t mCurrentPageEnd;
        uint32_t mCurrentPageIndex;

        char mCurrentPageData[VULCAN_MAX_PAGE_SIZE];
        int mCurrentPageSize;
};