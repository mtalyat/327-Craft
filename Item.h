#ifndef __ITEM_H__
#define __ITEM_H__

#include "Object.h"

// An item holds an ID and an amount for the given item within the game.
class Item
    : public Object
{
private:
    unsigned char id;
    unsigned char amount;

public:
    Item(unsigned char const itemId, unsigned int const startAmount = 0);
    ~Item();

    unsigned char getID() const { return id; }
    unsigned int getAmount() const { return amount; }
    void add(unsigned int const a);
    void remove(unsigned int const a);
    bool tryRemove(unsigned int const a);
    bool isEmpty() const { return amount == 0; }

    std::string toString() const override;
    std::wstring toWString() const override;
};

#endif // __ITEM_H__