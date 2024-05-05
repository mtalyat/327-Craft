#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <cstring>
#include <map>
#include "GameObject.h"
#include "FastNoiseLite.h"
#include "Point.h"
#include "Sprite.h"
#include "EngineData.h"
#include "Random.h"
#include "Modification.h"

// Stores blocks within the World in a 2D grid.
class Chunk
    : public GameObject
{
private:
    // the block IDs stored in this chunk
    unsigned char *data;
    // should the chunk redraw the sprite?
    bool shouldUpdateSprite;
    // is this chunk generated? (otherwise empty)
    bool generated;

    // map of modifications to be applied to this chunk
    std::map<int, Modification> *modifications;

private:
    // updates the sprite using the block IDs data
    void updateSprite(EngineData &ed);

protected:
    bool onUpdate(EngineData &ed) override;

public:
    Chunk(Point const &coords);
    ~Chunk();

    // marks this chunk as generated
    void markAsGenerated() { generated = true; }
    // checks if this chunk has been generated or not
    bool isGenerated() const { return generated; }

    // sets the block at the given x and y, and automatically updates the sprite
    void setBlock(int const x, int const y, BlockData const &block);
    // gets the block ID at the given x and y
    unsigned char getBlockID(int const x, int const y) const;

    // prints this Chunk to the screen
    void print(Point const &offset, Console &console) const;

    // converts the given position to Chunk coordinates
    static Point positionToCoords(Point const &pos);
    // converts the given position to a localized position
    static Point localizePosition(Point const &pos);
    // converts the given coordinates to a global position
    static Point coordsToPosition(Point const &coords);

    // gets a pointer to the modifications map for this Chunk
    std::map<int, Modification> *getModifications() const { return modifications; }
    // applies the modifications in this Chunk to the block IDs data
    void applyModifications(EngineData &ed);

    // the width of a Chunk, in blocks
    static const int WIDTH = 80;
    // the height of a Chunk, in blocks
    static const int HEIGHT = 24;
};

#endif // __CHUNK_H__