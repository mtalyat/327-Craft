#ifndef __SCENEINVENTORY_H__
#define __SCENEINVENTORY_H__

#include "Scene.h"

class ElementList;
class ElementText;

// The Inventory Scene within the game.
class SceneInventory
    : public Scene
{
private:
    int lastListIndex;

    ElementList *list;
    ElementText *nameText;
    ElementText *descriptionText;
    ElementText *amountText;
    ElementText *typeText;

protected:
    bool onInput(EngineData &data) override;
    void onEnter(EngineData &data) override;
    bool onUpdate(EngineData &data) override;

public:
    SceneInventory();
    ~SceneInventory();

    void init(EngineData &data) override;
};

#endif // __SCENEINVENTORY_H__