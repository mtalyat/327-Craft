#ifndef __SCENEGAME_H__
#define __SCENEGAME_H__

#include "Scene.h"
#include "World.h"
#include "Player.h"

// The Game Scene within the game.
class SceneGame
    : public Scene
{
private:
    World *world;

protected:
    bool onInput(EngineData &data) override;
    bool onUpdate(EngineData &data) override;
    void onDraw(EngineData &data) override;

public:
    SceneGame();
    ~SceneGame();

    void init(EngineData &data) override;
};

#endif // __SCENEGAME_H__