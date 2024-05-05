#include "Item.h"
#include "string_converter.h"

Item::Item(unsigned char const itemId, unsigned int const startAmount)
    : id(itemId), amount(startAmount)
{
}

Item::~Item()
{
}

void Item::add(unsigned int const a)
{
    amount += a;
}

void Item::remove(unsigned int const a)
{
    if (a >= amount)
    {
        amount = 0;
    }
    else
    {
        amount -= a;
    }
}

bool Item::tryRemove(unsigned int const a)
{
    if (a > amount)
    {
        // cannot remove, asking for too much/more than what is here
        return false;
    }
    else
    {
        // there is enough, so remove it
        amount -= a;
        return true;
    }
}

std::string Item::toString() const
{
    return "(" + std::to_string(id) + ": x" + std::to_string(amount) + ")";
}

std::wstring Item::toWString() const
{
    // for now
    return string_to_wstring(toString());
}
