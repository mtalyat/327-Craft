#include "Inventory.h"
#include "Item.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    // delete any remaining items in the inventory
    for (size_t i = itemsList.size() - 1; i >= 0; i--)
    {
        delete itemsList.at(i);
    }
}

bool Inventory::contains(unsigned char const id) const
{
    return items.find(id) != items.end();
}

unsigned int Inventory::getAmount(unsigned char const id) const
{
    if (contains(id))
    {
        return items.at(id)->getAmount();
    }
    else
    {
        return 0;
    }
}

void Inventory::add(unsigned char const id, unsigned int const amount)
{
    if (!contains(id))
    {
        Item *item = new Item(id, amount);
        items.emplace(id, item);
        itemsList.push_back(item);
    }
    else
    {
        items[id]->add(amount);
    }
}

void Inventory::remove(unsigned char const id, unsigned int const amount)
{
    if (!contains(id))
    {
        return;
    }

    Item *item = items[id];

    item->remove(amount);

    if (item->isEmpty())
    {
        // delete if necessary
        removeItem(id);
    }
}

bool Inventory::tryRemove(unsigned char const id, unsigned int const amount)
{
    if (!contains(id))
    {
        return false;
    }

    Item *item = items[id];

    if (item->tryRemove(amount))
    {
        // delete if necessary
        if (item->isEmpty())
        {
            removeItem(id);
        }

        return true;
    }

    return false;
}

void Inventory::removeItem(unsigned char const id)
{
    // completely remove the item with the id
    // assume it exists in the inventory

    Item *item = items[id];

    // remove from map and list
    items.erase(id);

    for (size_t i = 0; i < itemsList.size(); i++)
    {
        if (itemsList.at(i) == item)
        {
            itemsList.erase(itemsList.begin() + i);
            break;
        }
    }

    // delete completely
    delete item;
}
