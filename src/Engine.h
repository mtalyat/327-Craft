#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <vector>
#include <map>
#include "Object.h"
#include "EngineData.h"
#include "SceneLoader.h"
#include "CSVFile.h"

class Scene;

// The class that runs the game.
class Engine
    : public Object
{
private:
    bool isRunning;

    EngineData data;

    SceneLoader loader;

protected:
    void loadData();

public:
    Engine();
    virtual ~Engine();

    // Adds a Scene to the Engine.
    void addScene(std::wstring name, Scene *scene);

    // Runs the Engine.
    void run();

    // Quits the Engine.
    void quit();
};

#endif // __ENGINE_H__