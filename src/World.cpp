#include "World.h"
#include <cmath>

World *World::instance = nullptr;

World::World()
    : loadedChunks(), activeChunks(new Chunk *[2 * 2]), activeChunksSize(Point(2, 2)), activeChunksCoords(Point()), heightmap(), biomemap(), scalemap(), heightNoise(), biomeNoise(), scaleNoise()
{
    // TODO: dynamically set size based on console size

    int seed = random_range(10000);
    float const frequency = 0.01f;
    float const biomeFrequency = 0.001f;

    // initialize noises

    // general heightmap
    heightNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    heightNoise.SetSeed(seed);
    heightNoise.SetFrequency(frequency);
    heightNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
    heightNoise.SetFractalOctaves(4);
    heightNoise.SetFractalLacunarity(2.0f);
    heightNoise.SetFractalGain(0.5f);
    heightNoise.SetFractalWeightedStrength(0.0f);
    heightNoise.SetFractalPingPongStrength(2.0f);

    // biome map
    biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    biomeNoise.SetSeed(seed);
    biomeNoise.SetFrequency(biomeFrequency);
    biomeNoise.SetFractalType(FastNoiseLite::FractalType_None);
    biomeNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
    biomeNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);

    // scaling for between biomes
    scaleNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    scaleNoise.SetSeed(seed);
    scaleNoise.SetFrequency(biomeFrequency);
    scaleNoise.SetFractalType(FastNoiseLite::FractalType_None);
    scaleNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
    scaleNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_Distance2Sub);
}

World::~World()
{
    for (const auto &pair : heightmap)
    {
        delete[] pair.second;
    }
    for (const auto &pair : biomemap)
    {
        delete[] pair.second;
    }
    for (const auto &pair : scalemap)
    {
        delete[] pair.second;
    }
}

void World::updateActiveChunks(Point const &cameraPos, EngineData &ed)
{
    // get the proper chunk positions that should be in each spot
    // the top left of the 2x2 should be the x and y positions, divided and floored
    Point newChunkCoords = Chunk::positionToCoords(cameraPos);

    // now set accordingly if the position has changed
    if (newChunkCoords != activeChunksCoords)
    {
        activeChunksCoords = newChunkCoords;

        Point temp;

        // disable old active chunks
        for (int y = 0; y < activeChunksSize.y; y++)
        {
            for (int x = 0; x < activeChunksSize.x; x++)
            {
                if (activeChunks[y * activeChunksSize.x + x])
                {
                    activeChunks[y * activeChunksSize.x + x]->disable();
                }
            }
        }

        // set new chunks
        for (int y = 0; y < activeChunksSize.y; y++)
        {
            for (int x = 0; x < activeChunksSize.x; x++)
            {
                temp = Point(activeChunksCoords.x + x, activeChunksCoords.y + y);

                // make sure the chunk is generated
                generateChunkAt(temp, ed);

                loadedChunks[temp]->enable();

                // now set it
                activeChunks[y * activeChunksSize.x + x] = loadedChunks[temp];
            }
        }
    }
}

Chunk *World::getActiveChunkFromPosition(Point const &pos)
{
    return getActiveChunkFromCoords(Chunk::positionToCoords(pos));
}

Chunk *World::getActiveChunkFromCoords(Point const &coords)
{
    // get local coords
    Point local = coords - activeChunksCoords;

    // if in range
    if (local.x >= 0 && local.x < activeChunksSize.x &&
        local.y >= 0 && local.y < activeChunksSize.y)
    {
        // in range
        return activeChunks[local.y * activeChunksSize.x + local.x];
    }
    else
    {
        // not in range
        return nullptr;
    }
}

Chunk *World::getChunkFromPosition(Point const &pos)
{
    return getChunkFromCoords(Chunk::positionToCoords(pos));
}

Chunk *World::getChunkFromCoords(Point const &coords)
{
    // if the chunk exists, return it
    if (loadedChunks.find(coords) == loadedChunks.end())
    {
        // chunk does not exist, so create one quick
        loadedChunks[coords] = new Chunk(coords);
    }

    // chunk does exist
    return loadedChunks[coords];
}

unsigned char World::getBlockIDFromPosition(Point const &pos)
{
    Chunk *c = getChunkFromPosition(pos);

    if (c->isGenerated())
    {
        Point local = Chunk::localizePosition(pos);

        return c->getBlockID(local.x, local.y);
    }

    return INVALID_BLOCK;
}

void World::setBlockFromPosition(Point const &pos, BlockData const &block)
{
    Chunk *c = getChunkFromPosition(pos);

    Point local = Chunk::localizePosition(pos);

    c->setBlock(local.x, local.y, block);
}

int World::getGrassYAtXPosition(int const xPosition, EngineData &data)
{
    Point pos = Point(xPosition, 0);

    // convert to coordinate
    int xCoord = Chunk::positionToCoords(pos).x;

    // get position within chunk
    int localX = Chunk::localizePosition(pos).x;

    // get heightmap
    tryGenerateHeightmapAt(xCoord, data.getBiomeCount());

    // get grass Y
    return getGrassY(heightmap.at(xCoord)[localX], scalemap.at(xCoord)[localX], data.getBiome(biomemap.at(xCoord)[localX]));
}

void World::generateChunkAt(Point const &chunkCoords, EngineData &ed)
{
    // chunk should be there, if not one will be made
    Chunk *c = getChunkFromCoords(chunkCoords);

    // generate it if need be
    if (!c->isGenerated())
    {
        tryGenerateHeightmapAt(chunkCoords.x, ed.getBiomeCount());

        // now generate the chunk
        generateChunk(chunkCoords, heightmap.at(chunkCoords.x), biomemap.at(chunkCoords.x), scalemap.at(chunkCoords.x), ed);
        c->markAsGenerated();

        loadedChunks.emplace(chunkCoords, c);
        c->setParent(this);
    }
}

int World::getGrassY(float const height, float const scale, BiomeData *const biome)
{
    return (int)floor(scale * (height * (biome->getMaxTerrainHeight() - biome->getMinTerrainHeight()) + biome->getMinTerrainHeight()));
}

void World::generateChunk(Point const &chunkCoords, float *heightmap, int *biomemap, float *scalemap, EngineData &ed)
{
    // get modifications of surrounding chunks
    ModificationsGroup mods = ModificationsGroup();

    int index;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            index = y * 3 + x;

            mods.setModifications(index, getChunkFromCoords(chunkCoords + Point(x - 1, y - 1))->getModifications());
        }
    }

    // now generate data
    int grassY;
    int yy;
    Point position = Chunk::coordsToPosition(chunkCoords);
    BiomeData *biome;

    for (int x = 0; x < Chunk::WIDTH; x++)
    {
        biome = ed.getBiome(biomemap[x]);
        grassY = getGrassY(heightmap[x], scalemap[x], biome);

        for (int y = 0; y < Chunk::HEIGHT; y++)
        {
            yy = y + position.y;

            if (yy > grassY + biome->getSoilDepth())
            {
                // stone
                mods.addModification(x, y, Modification::block(3));

                // try to spawn underground structures

                // try to spawn deep, then normal, as deep is rarer
                // if not low enough or no ore was spawned, spawn normal underground
                if (yy <= grassY + biome->getSoilDepth() + 50 || !trySpawnStructures(x, y, mods, StructureData::SpawnLocation::DeepUnderground, biome, ed))
                {
                    trySpawnStructures(x, y, mods, StructureData::SpawnLocation::Underground, biome, ed);
                }
            }
            else if (yy >= grassY && yy >= biome->getSandLevel() && biome->getSandID() > 0)
            {
                // sand
                mods.addModification(x, y, Modification::block(biome->getSandID()));
            }
            else if (yy > grassY && biome->getSoilID() > 0)
            {
                // dirt
                mods.addModification(x, y, Modification::block(biome->getSoilID()));
            }
            else if (yy == grassY && yy <= biome->getSnowLevel() && biome->getSnowID() > 0)
            {
                // snow
                mods.addModification(x, y, Modification::block(biome->getSnowID()));
            }
            else if (yy == grassY && biome->getGrassID() > 0 && yy <= BiomeData::SEA_LEVEL)
            {
                // grass
                mods.addModification(x, y, Modification::block(biome->getGrassID()));
            }
            else if (yy >= BiomeData::SEA_LEVEL)
            {
                // water
                mods.addModification(x, y, Modification::block(11));
            }
            else
            {
                // above grass
                mods.addModification(x, y, Modification::block(0)); // air

                // try to spawn structures
                if (yy == grassY - 1)
                {
                    // surface structures
                    trySpawnStructures(x, y, mods, StructureData::SpawnLocation::Surface, biome, ed);
                }
                else if (yy <= biome->getSnowLevel() - 10 && yy <= grassY - 10)
                {
                    // sky structures
                    trySpawnStructures(x, y, mods, StructureData::SpawnLocation::Sky, biome, ed);
                }
            }
        }
    }
}

bool World::trySpawnStructures(int const x, int const y, ModificationsGroup &mods, StructureData::SpawnLocation location, BiomeData *const biome, EngineData &ed)
{
    // check all structures given from the biome of the type
    if (!biome->hasStructures(location))
    {
        return false;
    }

    StructureData *s;
    for (const auto &id : *biome->getStructureIDs(location))
    {
        s = ed.getStructure(id);

        // if random chance has it...
        if (s->shouldSpawn(random_range(0, 10000)))
        {
            // spawn the structure, and no more structures
            spawnStructure(x, y, mods, s->getID(), ed);
            return true;
        }
    }

    return false;
}

void World::spawnStructure(int const x, int const y, ModificationsGroup &mods, int const structureId, EngineData &ed)
{
    StructureData *structure = ed.getStructure(structureId);
    StructureVariationData *variation = ed.getStructureVariation(structure->getRandomVariationID());

    // x is the center, y is the bottom
    int xOffset = -variation->getWidth() / 2;
    int yOffset = -(variation->getHeight() - 1);
    int xPos, yPos;
    for (int xx = 0; xx < variation->getWidth(); xx++)
    {
        xPos = x + xOffset + xx;
        for (int yy = 0; yy < variation->getHeight(); yy++)
        {
            yPos = y + yOffset + yy;
            mods.addModification(xPos, yPos, Modification::block(variation->getData(xx, yy)), structure->getOverrideType());
        }
    }
}

bool World::onUpdate(EngineData &data)
{
    updateActiveChunks(*data.getCameraPos(), data);

    return true;
}

void World::onEnter(EngineData &data)
{
    if (!instance)
    {
        instance = this;
    }
}

void World::onExit(EngineData &data)
{
    if (this == instance)
    {
        instance = nullptr;
    }
}

void World::generateHeightmapAt(int const xCoord, int const biomeCount)
{
    float const scaleThreshold = 0.1f;

    // initialize int array
    float *yPositions = new float[Chunk::WIDTH];
    float *scales = new float[Chunk::WIDTH];
    int *biomeIds = new int[Chunk::WIDTH];

    float xx;
    float scale;

    // generate heights
    for (int x = 0; x < Chunk::WIDTH; x++)
    {
        xx = (float)(xCoord * Chunk::WIDTH + x);

        yPositions[x] = ((heightNoise.GetNoise(xx, xx) + 1.0f) / 2.0f);

        scale = ((scaleNoise.GetNoise(xx, xx) + 1.0f) / 2.0f);

        // adjust scale
        if (scale >= scaleThreshold)
        {
            scale = 1.0f;
        }
        else
        {
            // readjust
            scale /= scaleThreshold;
        }

        scales[x] = scale;

        biomeIds[x] = (int)floor(((biomeNoise.GetNoise(xx, xx) + 1.0f) / 2.0f) * biomeCount);
    }

    // set int array for reuse later
    heightmap.emplace(xCoord, yPositions);
    biomemap.emplace(xCoord, biomeIds);
    scalemap.emplace(xCoord, scales);
}

void World::tryGenerateHeightmapAt(int const xCoord, int const biomeCount)
{
    // if the heightmap/biomemap does not exist for this x, generate it
    if (heightmap.find(xCoord) == heightmap.end())
    {
        generateHeightmapAt(xCoord, biomeCount);
    }
}
