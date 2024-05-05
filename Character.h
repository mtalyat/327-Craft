#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity.h"
#include "Inventory.h"

// Base class for all Character entities with an inventory, such as a Player or NPC.
class Character
    : public Entity
{
private:
    // the inventory for this character
    Inventory inventory;

public:
    Character() {}
    ~Character() {}

    Inventory &getInventory() { return inventory; }
};

#endif // __CHARACTER_H__