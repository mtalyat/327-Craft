#ifndef __SCENEMENU_H__
#define __SCENEMENU_H__

#include "Scene.h"

// The Main Menu Scene within the game.
class SceneMenu
    : public Scene
{
public:
    SceneMenu();
    ~SceneMenu();

    void init(EngineData &data) override;
};

#endif // __SCENEMENU_H__