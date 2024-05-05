#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>
#include <map>
#include "Point.h"
#include "GameObject.h"
#include "Chunk.h"
#include "EngineData.h"
#include "Random.h"
#include "ModificationsGroup.h"

#define INVALID_BLOCK 255

// The world in which the player moves around. Handles loading, generating and unloading Chunks.
class World
    : public GameObject
{
private:
    std::map<Point, Chunk *> loadedChunks;
    Chunk **activeChunks;
    Point activeChunksSize;
    Point activeChunksCoords;
    std::map<int, float *> heightmap;
    std::map<int, int *> biomemap;
    std::map<int, float *> scalemap;
    FastNoiseLite heightNoise;
    FastNoiseLite biomeNoise;
    FastNoiseLite scaleNoise;

    static World *instance;

private:
    void tryGenerateHeightmapAt(int const xCoord, int const biomeCount);
    void generateHeightmapAt(int const xCoord, int const biomeCount);
    void generateChunkAt(Point const &chunkPos, EngineData &ed);
    int getGrassY(float const height, float const scale, BiomeData *const biome);
    void generateChunk(Point const &chunkCoords, float *heightmap, int *biomemap, float *scalemap, EngineData &ed);
    bool trySpawnStructures(int const x, int const y, ModificationsGroup &mods, StructureData::SpawnLocation location, BiomeData *const biome, EngineData &ed);
    void spawnStructure(int const x, int const y, ModificationsGroup &mods, int const structureId, EngineData &ed);

protected:
    bool onUpdate(EngineData &data) override;
    void onEnter(EngineData &data) override;
    void onExit(EngineData &data) override;

public:
    World();
    ~World();

    void updateActiveChunks(Point const &cameraPos, EngineData &ed);

    Chunk *getActiveChunkFromPosition(Point const &pos);
    Chunk *getActiveChunkFromCoords(Point const &coords);

    Chunk *getChunkFromPosition(Point const &pos);
    Chunk *getChunkFromCoords(Point const &coords);

    unsigned char getBlockIDFromPosition(Point const &pos);
    void setBlockFromPosition(Point const &pos, BlockData const &block);

    int getGrassYAtXPosition(int const xPosition, EngineData &ed);

    static World *getInstance() { return instance; }
};

#endif // __WORLD_H__