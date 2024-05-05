#include "SceneLoader.h"

SceneLoader::SceneLoader()
    : scenes(), nextScene(nullptr), activeScene(nullptr)
{
}

SceneLoader::~SceneLoader()
{
    // delete any scenes
    for (const auto &s : scenes)
    {
        delete s.second;
    }
}

void SceneLoader::init(EngineData &data)
{
    for (const auto &scene : scenes)
    {
        scene.second->init(data);
    }
}

void SceneLoader::addScene(std::wstring name, Scene *scene)
{
    if (scene == nullptr)
        return;

    scenes[name] = scene;

    if (activeScene == nullptr)
    {
        activeScene = scene;
    }
}

Scene *SceneLoader::getActive() const
{
    return activeScene;
}

void SceneLoader::setNextActive(const std::wstring &name)
{
    if (hasScene(name))
    {
        // set to scene
        nextScene = scenes[name];
    }
    else
    {
        // does not have the scene with name, do nothing
        nextScene = nullptr;
    }
}

void SceneLoader::loadNext(EngineData &data)
{
    // do nothing if next null
    if (nextScene == nullptr)
        return;

    // do nothing if already there
    if (nextScene == activeScene)
        return;

    // leave current scene
    activeScene->exit(data);

    // set new scene
    activeScene = nextScene;

    // enter new scene
    activeScene->enter(data);

    nextScene = nullptr;
}

bool SceneLoader::hasScene(const std::wstring &name)
{
    // has scene if the iterator did not reach the end
    return scenes.find(name) != scenes.end();
}
