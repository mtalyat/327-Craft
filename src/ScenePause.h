#ifndef __SCENEPAUSE_H__
#define __SCENEPAUSE_H__

#include "Scene.h"

class ElementManager;

// The Pause Scene within the game.
class ScenePause
    : public Scene
{
private:
    ElementManager *manager;

protected:
    bool onInput(EngineData &data) override;
    void onEnter(EngineData &data) override;

public:
    ScenePause();
    ~ScenePause() {}

    void init(EngineData &data) override;
};

#endif // __SCENEPAUSE_H__