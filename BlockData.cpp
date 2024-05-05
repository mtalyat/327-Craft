#include "BlockData.h"

BlockData::BlockData()
    : display(' ')
{
}

BlockData::~BlockData()
{
}

void BlockData::loadData(const std::vector<std::wstring> &lineData)
{
    // 0 is ID
    // 1 is item ID
    // 2 is display
    // 3 is color ID
    // 4 is drop ID
    // 5 is drop amount
    // 6 is collisions?

    id = stringToInt(lineData.at(0));
    itemId = stringToInt(lineData.at(1));
    display = lineData.at(2).at(0);
    colorId = stringToUnsignedChar(lineData.at(3));
    dropId = stringToInt(lineData.at(4));
    dropAmount = stringToInt(lineData.at(5));
    collisions = stringToBool(lineData.at(6));
}
