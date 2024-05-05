#include "StructureVariationData.h"

void StructureVariationData::loadData(const std::vector<std::wstring> &lineData)
{
    // 0 is id
    // 1 is width
    // 2 is data

    id = stringToInt(lineData[0]);
    width = stringToInt(lineData[1]);
    int length;
    data = stringToUnsignedCharArray(lineData[2], length);
    height = length / width;
}

StructureVariationData::StructureVariationData()
    : width(0), height(0), data(nullptr)
{
}

StructureVariationData::~StructureVariationData()
{
    if (data)
        delete[] data;
}

unsigned char StructureVariationData::getData(int const x, int const y) const
{
    return data[y * width + x];
}
