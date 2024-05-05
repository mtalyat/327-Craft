#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__

#include <string>
#include "CSVObject.h"

// Holds data for an item.
class ItemData
    : public CSVObject
{
private:
    unsigned char blockId;
    std::wstring name;
    std::wstring description;

public:
    ItemData();
    ~ItemData();

    unsigned char getBlockID() const { return blockId; }
    std::wstring const &getName() const { return name; }
    std::wstring const &getDescription() const { return description; }

    void loadData(const std::vector<std::wstring> &lineData);
};

#endif // __ITEMDATA_H__