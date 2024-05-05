#ifndef __STRUCTUREVARIATION_H__
#define __STRUCTUREVARIATION_H__

#include "CSVObject.h"

// Holds the block ID data for a variation of a structure.
class StructureVariationData
    : public CSVObject
{
private:
    int width;
    int height;
    unsigned char *data;

public:
    StructureVariationData();
    ~StructureVariationData();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    unsigned char getData(int const x, int const y) const;

    void loadData(const std::vector<std::wstring> &lineData) override;
};

#endif // __STRUCTUREVARIATION_H__