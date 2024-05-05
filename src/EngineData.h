#ifndef __ENGINEDATA_H__
#define __ENGINEDATA_H__

#include <string>
#include <map>
#include <vector>
#include "Object.h"
#include "Console.h"
#include "BlockData.h"
#include "ItemData.h"
#include "StructureData.h"
#include "StructureVariationData.h"
#include "CSVFile.h"
#include "Point.h"
#include "BiomeData.h"

// Data for the Engine that can be passed around during each action (init, input, enter, update, exit, draw, and so on).
class EngineData
    : public Object
{
private:
    int input;

    std::wstring nextSceneName;
    bool loadNewScene;

    std::map<int, BlockData *> blocks;
    std::map<int, ItemData *> items;
    std::map<int, StructureData *> structures;
    std::map<int, StructureVariationData *> structureVariations;
    std::map<int, BiomeData *> biomes;

    Point *cameraPos;

    bool *running;

private:
    // assume T is of type CSVObject, and M is a map
    template <typename T, typename M>
    void initData(CSVFile const &file, M *data)
    {
        T *temp;

        for (int i = 0; i < file.getLineCount(); i++)
        {
            temp = new T();
            temp->loadData(file.getLine(i));
            data->emplace(temp->getID(), temp);
        }
    }

public:
    Console console;

public:
    EngineData();
    ~EngineData();

    void initItems(CSVFile const &file);
    void initBlocks(CSVFile const &file);
    void initStructures(CSVFile const &structuresFile, CSVFile const &structureVariationsFile);
    void initBiomes(CSVFile const &file);

    void setNextScene(const std::wstring &name);
    const std::wstring &getNextScene();

    bool shouldLoadNewScene() const { return loadNewScene; }

    void setInput(const int i) { input = i; }
    int getInput() const { return input; }

    void setCameraPos(Point *p) { cameraPos = p; }
    Point *getCameraPos() const { return cameraPos; }

    ItemData *getItem(int const id) const;
    ItemData *getItemFromBlockIndex(int const id) const;
    BlockData *getBlock(int const id) const;
    BiomeData *getBiome(int const id) const;
    int getBiomeCount() const { return biomes.size(); }

    void initQuit(bool *const q) { running = q; }
    void quit() { *running = false; }

    StructureData *getStructure(int const id) const;
    StructureVariationData *getStructureVariation(int const id) const;
};

#endif // __ENGINEDATA_H__