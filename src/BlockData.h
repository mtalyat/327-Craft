#ifndef __BLOCKDATA_H__
#define __BLOCKDATA_H__

#include "CSVObject.h"

// Holds data for blocks.
class BlockData
    : public CSVObject
{
private:
    // the corresponding item ID
    int itemId;
    // the character printed on the screen for this block
    wchar_t display;
    // the color combo pair id
    unsigned short colorId;
    // the item ID that is put into the player's inventory when the block is broken
    int dropId;
    // the amount of items that the player gets when the block is broken
    int dropAmount;
    // does this block collide with entities?
    bool collisions;

public:
    BlockData();
    ~BlockData();

    int getID() const { return id; }
    int getItemID() const { return itemId; }
    wchar_t getDisplay() const { return display; }
    unsigned short getColorID() const { return colorId; }
    int getDropID() const { return dropId; }
    int getDropAmount() const { return dropAmount; }
    bool hasCollisions() const { return collisions; }

    void loadData(const std::vector<std::wstring> &lineData) override;
};

#endif // __BLOCKDATA_H__