#include "Scene.h"

bool Scene::input(EngineData &data)
{
    bool input = false;

    GameObject *go;

    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        go = gameObjects.at(i);
        if (go->getEnabled())
        {
            input = go->input(data) || input;
        }
    }

    return onInput(data) || input;
}

void Scene::enter(EngineData &data)
{
    GameObject *go;

    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        go = gameObjects.at(i);
        if (go->getEnabled())
        {
            go->enter(data);
        }
    }

    // if there is a camera, set the data to it
    if (Camera::getMain())
    {
        data.setCameraPos(&Camera::getMain()->getLocalPosition());
    }

    onEnter(data);
}

bool Scene::update(EngineData &data)
{
    bool update = false;

    GameObject *go;

    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        go = gameObjects.at(i);
        if (go->getEnabled())
        {
            update = go->update(data) || update;
        }
    }

    return onUpdate(data) || update;
}

void Scene::exit(EngineData &data)
{

    GameObject *go;

    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        go = gameObjects.at(i);
        if (go->getEnabled())
        {
            go->exit(data);
        }
    }

    onExit(data);
}

void Scene::draw(EngineData &data)
{

    GameObject *go;

    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        go = gameObjects.at(i);
        if (go->getEnabled())
        {
            go->draw(data);
        }
    }

    onDraw(data);
}

Scene::Scene()
    : gameObjects()
{
}

Scene::~Scene()
{
    // destroy all game objects in the scene
    for (size_t i = gameObjects.size() - 1; i >= 0; i--)
    {
        delete gameObjects.at(i);
    }
}

Scene::Scene(const Scene &other)
{
    gameObjects = other.gameObjects;
}

Scene &Scene::operator=(const Scene &other)
{
    gameObjects = other.gameObjects;

    return *this;
}

void Scene::addGameObject(GameObject *go)
{
    gameObjects.push_back(go);
}
