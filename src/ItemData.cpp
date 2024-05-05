#include "ItemData.h"
ItemData::ItemData()
    : name(), description()
{
}

ItemData::~ItemData()
{
}

void ItemData::loadData(const std::vector<std::wstring> &lineData)
{
    // o is ID
    // 1 is name
    // 2 is description

    id = stringToInt(lineData[0]);
    blockId = stringToUnsignedChar(lineData[1]);
    name = lineData[2];
    description = lineData[3];
}
