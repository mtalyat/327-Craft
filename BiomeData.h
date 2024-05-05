#ifndef __BIOMEDATA_H__
#define __BIOMEDATA_H__

#include <map>
#include <vector>
#include "CSVObject.h"
#include "StructureData.h"

// Holds data about biomes.
class BiomeData
    : public CSVObject
{
private:
    // the block ID for the top block on the surface
    unsigned char grassId;
    // the block ID for the (sub surface) blocks under the surface block
    unsigned char soilId;
    // the amount of sub surface blocks before stone
    int soilDepth;
    // the block ID for blocks on the surface, but below water
    unsigned char sandId;
    // the block ID for surface blocks above the snow level
    unsigned char snowId;
    // the minimum height for terrain in this biome
    int minTerrainHeight;
    // the maximum height for terrain in this biome
    int maxTerrainHeight;
    // the highest level at which sand will spawn
    int sandLevel;
    // the lowest level at which snow will spawn
    int snowLevel;

    // the structures that will spawn within this biome
    std::map<StructureData::SpawnLocation, std::vector<int>> structures;

private:
    // adds the structure IDs to the map of structure IDs
    void addStructures(StructureData::SpawnLocation const location, int *const arr, int const length);

public:
    BiomeData();
    ~BiomeData();

    unsigned char getGrassID() const { return grassId; }
    unsigned char getSoilID() const { return soilId; }
    int getSoilDepth() const { return soilDepth; }
    unsigned char getSandID() const { return sandId; }
    unsigned char getSnowID() const { return snowId; }
    int getMinTerrainHeight() const { return minTerrainHeight; }
    int getMaxTerrainHeight() const { return maxTerrainHeight; }
    int getSandLevel() const { return sandLevel; }
    int getSnowLevel() const { return snowLevel; }

    // checks if there is at least 1 structure for the given spawn location
    bool hasStructures(StructureData::SpawnLocation const location) const;
    // gets the list of structure IDs for the given spawn location
    std::vector<int> *getStructureIDs(StructureData::SpawnLocation const location);

    void loadData(const std::vector<std::wstring> &lineData) override;

    // the highest level at which water will spawn
    static const int SEA_LEVEL = 0;
};

#endif // __BIOMEDATA_H__