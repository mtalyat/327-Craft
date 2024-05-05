#include "EngineData.h"

EngineData::EngineData()
    : nextSceneName(L""), loadNewScene(false), blocks(), items(), cameraPos(nullptr), running(nullptr), console()
{
}

EngineData::~EngineData()
{
    // TODO: delete blocks and items values
}

void EngineData::setNextScene(const std::wstring &name)
{
    nextSceneName = name;
    loadNewScene = true;
}

const std::wstring &EngineData::getNextScene()
{
    loadNewScene = false;
    return nextSceneName;
}

void EngineData::initItems(CSVFile const &file)
{
    initData<ItemData, std::map<int, ItemData *>>(file, &items);
}

void EngineData::initBlocks(CSVFile const &file)
{
    initData<BlockData, std::map<int, BlockData *>>(file, &blocks);
}

void EngineData::initStructures(CSVFile const &structuresFile, CSVFile const &structureVariationsFile)
{
    initData<StructureData, std::map<int, StructureData *>>(structuresFile, &structures);
    initData<StructureVariationData, std::map<int, StructureVariationData *>>(structureVariationsFile, &structureVariations);
}

void EngineData::initBiomes(CSVFile const &file)
{
    initData<BiomeData, std::map<int, BiomeData *>>(file, &biomes);
}

ItemData *EngineData::getItem(int const id) const
{
    return items.at(id);
}

ItemData *EngineData::getItemFromBlockIndex(int const id) const
{
    return getItem(getBlock(id)->getItemID());
}

BlockData *EngineData::getBlock(int const id) const
{
    return blocks.at(id);
}

BiomeData *EngineData::getBiome(int const id) const
{
    return biomes.at(id);
}

StructureData *EngineData::getStructure(int const id) const
{
    return structures.at(id);
}

StructureVariationData *EngineData::getStructureVariation(int const id) const
{
    return structureVariations.at(id);
}