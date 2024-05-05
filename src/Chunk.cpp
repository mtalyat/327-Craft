#include "Chunk.h"

Chunk::Chunk(Point const &coords)
    : GameObject(), data(new unsigned char[WIDTH * HEIGHT]), shouldUpdateSprite(false), generated(false), modifications(new std::map<int, Modification>())
{
    // set all data to 0
    std::memset(data, 0, WIDTH * HEIGHT);

    // new sprite
    setSprite(new Sprite(WIDTH, HEIGHT));

    setPosition(coordsToPosition(coords));
}

Chunk::~Chunk()
{
    GameObject::~GameObject();
    delete[] data;
    delete modifications;
}

void Chunk::setBlock(int const x, int const y, BlockData const &block)
{
    // set data
    data[y * WIDTH + x] = block.getID();

    // update sprite to reflect it
    getSprite()->set(x, y, block.getDisplay(), block.getColorID());
}

unsigned char Chunk::getBlockID(int const x, int const y) const
{
    return data[y * WIDTH + x];
}

void Chunk::print(Point const &offset, Console &console) const
{
    getSprite()->print(offset.x, offset.y, console);
}

Point Chunk::positionToCoords(Point const &pos)
{
    return Point((int)floor(pos.x / (float)Chunk::WIDTH), (int)floor(pos.y / (float)Chunk::HEIGHT));
}

Point Chunk::localizePosition(Point const &pos)
{
    return Point(((pos.x % WIDTH) + WIDTH) % WIDTH, ((pos.y % HEIGHT) + HEIGHT) % HEIGHT);
}

Point Chunk::coordsToPosition(Point const &coords)
{
    return coords * Point(Chunk::WIDTH, Chunk::HEIGHT);
}

void Chunk::updateSprite(EngineData &ed)
{
    int index;
    BlockData *block;
    Sprite *sprite = getSprite();

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            index = y * WIDTH + x;

            // get the block data for the block stored with this ID
            block = ed.getBlock(data[index]);

            // set display and color accordingly
            sprite->set(x, y, block->getDisplay(), block->getColorID());
        }
    }
}

void Chunk::applyModifications(EngineData &ed)
{
    if (!generated)
    {
        // only apply if generated
        return;
    }

    Sprite *sprite = getSprite();
    BlockData *block;
    for (const auto &mod : *modifications)
    {
        block = ed.getBlock(mod.second.data);

        data[mod.first] = mod.second.data;

        // debug, show chunk borders
        // if (mod.first < WIDTH || mod.first % WIDTH == 0)
        // {
        //     sprite->set(mod.first, block->getDisplay(), 1);
        // }
        // else
        // {
        //     sprite->set(mod.first, block->getDisplay(), block->getColorID());
        // }

        sprite->set(mod.first, block->getDisplay(), block->getColorID());
    }

    // all done and updated, get rid fo the modifications
    modifications->clear();
}

bool Chunk::onUpdate(EngineData &ed)
{
    // TODO: only update if data was changed, or position moved
    if (modifications->size() > 0)
    {
        applyModifications(ed);
    }

    return true;
}
