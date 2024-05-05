#ifndef __MODIFICATIONSGROUP_H__
#define __MODIFICATIONSGROUP_H__

#include <map>
#include "Object.h"
#include "Chunk.h"
#include "Modification.h"
#include "StructureData.h"

// Holds a 3x3 grid of maps with modifications from nearby chunks.
// Allows for easy modifications of the center chunk, as well as nearby chunks for generating structures that may "bleed" into the neighboring chunks.
class ModificationsGroup
{
    std::map<int, Modification> **modifications;

public:
    ModificationsGroup();
    ~ModificationsGroup();

    void setModifications(int const index, std::map<int, Modification> *mods);
    void addModification(int x, int y, Modification const d, StructureData::OverrideType const orideType = StructureData::OverrideType::Partial);
};

#endif // __MODIFICATIONSGROUP_H__