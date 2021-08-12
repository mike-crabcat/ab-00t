#include <memory>
#include <cstring>

#include "kaitai/kaitaistruct.h"
#include "VulcanTriReader.h"
#include "fastlz.h"
#include "endian.h"

VulcanTriReader::VulcanTriReader(const std::string path) {

    mCurrentPageSize = 0;
    mCurrentPageStart = 0;
    mCurrentPageEnd = 0;
    mCurrentOffset = 0;

    mFstream.open(path);
    if(!mFstream.is_open())
        throw std::runtime_error("Failed to open path");

    mDataStream = std::make_shared<kaitai::kstream>(&mFstream);
    mDataStruct = std::make_shared<vulcan_00t_t>(mDataStream.get());
}


void VulcanTriReader::readHeader(int& numVertex, int& numTriangles) {

    //Read magic bytes to check

    //Read sizes
    seek(72);
    read(&numVertex, 4);
    numVertex = be32toh(numVertex);
    seek(96);
    read(&numTriangles, 4);
    numTriangles = be32toh(numTriangles);
}

bool VulcanTriReader::readVertexBuffer(double* buffer, size_t bufferSize) {
    int numVertex, numTriangles;
    readHeader(numVertex, numTriangles);
    
    //Vertices start at this offset
    seek(72+24+24);

    size_t readLength = sizeof(double) * 3 * numVertex;
    if(readLength > bufferSize) return false;
    
    read(buffer, sizeof(double) * 3 * numVertex);

    //Fix endianness of buffer
    for(size_t i=0;i<3 * numVertex;i++) {
        buffer[i] = be64toh(buffer[i]);
    }


    return true;
}

bool VulcanTriReader::readTriangleBuffer(uint32_t* buffer, size_t bufferSize) {
    int numVertex, numTriangles;
    readHeader(numVertex, numTriangles);

    size_t readLength = sizeof(uint32_t) * 3 * numTriangles;
    if(readLength > bufferSize) return false;
    
    //Vertices start at this offset
    seek(72+24+24+24*numVertex);
    
    read(buffer, sizeof(uint32_t) * 3 * numTriangles);

    //Fix endianness of buffer
    for(size_t i=0;i<3 * numTriangles;i++) {
        buffer[i] = be32toh(buffer[i]);
    }

    return true;
}

void VulcanTriReader::seek(uint32_t offset) {

    //Within current page? just change current offset within page
    if(offset >= mCurrentPageStart && offset < mCurrentPageEnd) {
        mCurrentOffset = offset;
    }
    //Load new page based on offset
    else {
        uint32_t pageIndex = offset / mDataStruct->compression_block_size();
        ldiv_t l3Div = std::div((int64_t)pageIndex, (uint32_t)256);
        ldiv_t l2Div = std::div((int64_t)l3Div.quot, (uint32_t)256);
        ldiv_t l1Div = std::div((int64_t)l2Div.quot, (uint32_t)256);
        ldiv_t l0Div = std::div((int64_t)l1Div.quot, (uint32_t)256);
            
        if(l0Div.quot != 0) throw std::runtime_error("Offset too big");

        vulcan_00t_t::page_t* page = mDataStruct->root()->children()->at(l0Div.rem)->children()->at(l1Div.rem)->children()->at(l2Div.rem)->children()->at(l3Div.rem)->page();

        //Decompress page into current page buffer
        mCurrentPageSize = fastlz_decompress(page->compressed_data().c_str(), page->compressed_data_size(), mCurrentPageData, sizeof(mCurrentPageData));

        mCurrentOffset = offset;
        mCurrentPageStart = pageIndex * mDataStruct->compression_block_size();
        mCurrentPageEnd = mCurrentPageStart + mDataStruct->compression_block_size();
        mCurrentPageIndex = pageIndex;
    }
}

void VulcanTriReader::read(void* target, uint32_t length) {
    size_t targetOffset = 0;
    while(true) {
        uint32_t a = mCurrentOffset - mCurrentPageStart;
        uint32_t b = std::min(a + length, mCurrentPageEnd);
        std::memcpy((char*)target + targetOffset, &mCurrentPageData[a], b - a);
        targetOffset += b - a;
        length -= b - a;
        mCurrentOffset += b - a;
        if(length > 0) {
            seek(mCurrentOffset);
        }
        else
            break;
    }
}