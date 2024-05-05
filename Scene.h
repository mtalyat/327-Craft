#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "Object.h"
#include "GameObject.h"
#include "EngineData.h"
#include "Camera.h"

// The base class for all Scenes within the game.
class Scene
    : public Object
{
protected:
    std::vector<GameObject *> gameObjects;

protected:
    virtual bool onInput(EngineData &data) { return false; }
    virtual void onEnter(EngineData &data) {}
    virtual bool onUpdate(EngineData &data) { return false; }
    virtual void onExit(EngineData &data) {}
    virtual void onDraw(EngineData &data) {}

    void addGameObject(GameObject *go);

public:
    Scene();
    virtual ~Scene();

    Scene(const Scene &other);
    Scene &operator=(const Scene &other);

    virtual void init(EngineData &data) {}

    bool input(EngineData &data);
    void enter(EngineData &data);
    bool update(EngineData &data);
    void exit(EngineData &data);
    void draw(EngineData &data);
};

#endif // __SCENE_H__