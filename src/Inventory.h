#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <map>
#include <string>
#include <vector>
#include "Object.h"

class Item;

// The inventory holds a collection of Items, that can be added and removed from.
class Inventory
    : public Object
{
private:
    // list of items for quick lookup
    std::map<unsigned char, Item *> items;
    // list of items for player for easy access
    std::vector<Item *> itemsList;

private:
    void removeItem(unsigned char const id);

public:
    Inventory();
    ~Inventory();

    bool contains(unsigned char const id) const;
    unsigned int getAmount(unsigned char const id) const;
    void add(unsigned char const id, unsigned int const amount);
    void remove(unsigned char const id, unsigned int const amount);
    bool tryRemove(unsigned char const id, unsigned int const amount);
    bool isEmpty() const { return itemsList.size() == 0; }
    Item *get(int const index) const { return itemsList.at(index); }
    size_t size() const { return itemsList.size(); }
};

#endif // __INVENTORY_H__