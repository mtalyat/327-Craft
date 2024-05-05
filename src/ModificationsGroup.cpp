#include "ModificationsGroup.h"

ModificationsGroup::~ModificationsGroup()
{
    // do not delete the data, just the pointer to the datas
    delete[] modifications;
}

void ModificationsGroup::setModifications(int const index, std::map<int, Modification> *mods)
{
    modifications[index] = mods;
}

void ModificationsGroup::addModification(int x, int y, Modification const d, StructureData::OverrideType const orideType)
{
    // in center to start
    int chunkX = 1, chunkY = 1;
    if (x < 0)
    {
        chunkX--;
        x += Chunk::WIDTH;

        if (y < 0)
        {
            y += Chunk::HEIGHT;
            chunkY--;
        }
        else if (y >= Chunk::HEIGHT)
        {
            y -= Chunk::HEIGHT;
            chunkY++;
        }
    }
    else if (x >= Chunk::WIDTH)
    {
        chunkX++;
        x -= Chunk::WIDTH;

        if (y < 0)
        {
            y += Chunk::HEIGHT;
            chunkY--;
        }
        else if (y >= Chunk::HEIGHT)
        {
            y -= Chunk::HEIGHT;
            chunkY++;
        }
    }
    else
    {
        if (y < 0)
        {
            y += Chunk::HEIGHT;
            chunkY--;
        }
        else if (y >= Chunk::HEIGHT)
        {
            y -= Chunk::HEIGHT;
            chunkY++;
        }
    }

    int index = chunkY * 3 + chunkX;
    int indexInChunk = y * Chunk::WIDTH + x;

    // now that propert x/y and chunk is found, add modification
    switch (orideType)
    {
    case StructureData::All:
        // set regardless of what is here
        (*modifications[index])[indexInChunk] = d;
        break;
    case StructureData::Partial:
        // only set if incoming block != 0, or if there is nothing there
        if (d.data > 0 || modifications[index]->find(indexInChunk) == modifications[index]->end() || modifications[index]->at(indexInChunk).data == 0)
        {
            (*modifications[index])[indexInChunk] = d;
        }
        break;
    default:
        // do not override, only set if nothing there (literally nothing, or if it is just air)
        if (modifications[index]->find(indexInChunk) == modifications[index]->end() || modifications[index]->at(indexInChunk).data == 0)
        {
            (*modifications[index])[indexInChunk] = d;
        }
        break;
    }
}

ModificationsGroup::ModificationsGroup()
    : modifications(new std::map<int, Modification> *[9])
{
}
