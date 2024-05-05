#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include "CSVObject.h"
#include "Random.h"

// Holds data for a structure.
class StructureData
    : public CSVObject
{
public:
    enum SpawnLocation
    {
        Surface = 0,         // spawns at grassY - 1
        Underground = 1,     // spawns below soil
        DeepUnderground = 2, // spawns 50 blocks below soil
        Sky = 3,             // 10 blocks above snow level
    };

    enum OverrideType
    {
        None = 0,    // nothing is overriden - if there is something there, place nothing
        Partial = 1, // only non-0 blocks override the existing blocks
        All = 2,     // everything, including 0 blocks overrides the existing blocks
    };

private:
    int numberOfVariations;
    OverrideType overrideType;
    SpawnLocation spawnLocation;
    int spawnChance;

    unsigned char *variationIds;

public:
    StructureData();
    ~StructureData();

    unsigned char getRandomVariationID() const { return variationIds[random_range(numberOfVariations)]; }
    OverrideType getOverrideType() const { return overrideType; }
    SpawnLocation getSpawnLocation() const { return spawnLocation; }
    bool shouldSpawn(int const randomValue) const { return spawnChance > randomValue; }

    void loadData(const std::vector<std::wstring> &lineData) override;
};

#endif // __STRUCTURE_H__