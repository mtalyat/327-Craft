#ifndef __SCENELOADER_H__
#define __SCENELOADER_H__

#include <map>
#include <string>
#include "Scene.h"
#include "Object.h"
#include "EngineData.h"

// Handles loading and unloading Scenes.
class SceneLoader
    : public Object
{
private:
    std::map<std::wstring, Scene *> scenes;
    Scene *nextScene;
    Scene *activeScene;

    // checks if the sceneloader has a scene with the given name
    bool hasScene(const std::wstring &name);

public:
    SceneLoader();
    ~SceneLoader();

    // Initializes all Scenes within the SceneLoader.
    void init(EngineData &data);

    // Adds a Scene to the SceneLoader.
    void addScene(std::wstring name, Scene *scene);

    Scene *getActive() const;
    void setNextActive(const std::wstring &name);

    // exits the active scene, and loads the next one, if there is a next one
    void loadNext(EngineData &data);
};

#endif // __SCENELOADER_H__