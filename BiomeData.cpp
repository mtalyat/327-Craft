#include "BiomeData.h"
void BiomeData::loadData(const std::vector<std::wstring> &lineData)
{
    // id,grass_id,soil_id,soil_depth,sand_id,min_terrain_height,max_terrain_height,sea_level,sand_level,snow_level
    // 0 is id
    // 1 is grass id
    // 2 is soil id
    // 3 is soil depth
    // 4 is sand id
    // 5 is snow id
    // 6 is min terrain height
    // 7 is max terrain height
    // 8 is sea level
    // 9 is sand level
    // 10 is snow level
    // 11 is surface
    // 12 is underground
    // 13 is deep underground
    // 14 is sky

    id = stringToInt(lineData.at(0));
    grassId = stringToUnsignedChar(lineData.at(1));
    soilId = stringToUnsignedChar(lineData.at(2));
    soilDepth = stringToInt(lineData.at(3));
    sandId = stringToInt(lineData.at(4));
    snowId = stringToInt(lineData.at(5));
    minTerrainHeight = stringToInt(lineData.at(6));
    maxTerrainHeight = stringToInt(lineData.at(7));
    sandLevel = stringToInt(lineData.at(8));
    snowLevel = stringToInt(lineData.at(9));

    int length;
    int *temp = stringToIntArray(lineData.at(10), length);
    addStructures(StructureData::SpawnLocation::Surface, temp, length);

    temp = stringToIntArray(lineData.at(11), length);
    addStructures(StructureData::SpawnLocation::Underground, temp, length);

    temp = stringToIntArray(lineData.at(12), length);
    addStructures(StructureData::SpawnLocation::DeepUnderground, temp, length);

    temp = stringToIntArray(lineData.at(13), length);
    addStructures(StructureData::SpawnLocation::Sky, temp, length);
}

BiomeData::BiomeData()
{
}

BiomeData::~BiomeData()
{
}

bool BiomeData::hasStructures(StructureData::SpawnLocation const location) const
{
    return structures.find(location) != structures.end() && structures.at(location).size() > 0;
}

std::vector<int> *BiomeData::getStructureIDs(StructureData::SpawnLocation const location)
{
    // if it does not exist, return null
    if (structures.find(location) == structures.end())
    {
        return nullptr;
    }

    return &structures.at(location);
}

void BiomeData::addStructures(StructureData::SpawnLocation const location, int *const arr, int const length)
{
    if (structures.find(location) == structures.end())
    {
        // if no list yet, add it
        structures.emplace(location, std::vector<int>());
    }

    std::vector<int> &list = structures.at(location);

    for (int i = 0; i < length; i++)
    {
        list.push_back(arr[i]);
    }
}
