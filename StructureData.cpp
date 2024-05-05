#include "StructureData.h"
StructureData::StructureData()
    : numberOfVariations(0), overrideType(None), spawnLocation(Surface), spawnChance(0), variationIds(nullptr)
{
}

StructureData::~StructureData()
{
    if (variationIds)
        delete[] variationIds;
}

void StructureData::loadData(const std::vector<std::wstring> &lineData)
{
    // 0 is id
    // 1 is override blocks
    // 2 is structure variation indexes
    id = stringToInt(lineData[0]);
    overrideType = static_cast<OverrideType>(stringToInt(lineData[1]));
    spawnLocation = static_cast<SpawnLocation>(stringToInt(lineData[2]));
    spawnChance = stringToInt(lineData[3]);
    variationIds = stringToUnsignedCharArray(lineData[4], numberOfVariations);
}
