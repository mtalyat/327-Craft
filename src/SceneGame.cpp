#include "SceneGame.h"

bool SceneGame::onUpdate(EngineData &data)
{
    // always draw
    return true;
}

void SceneGame::onDraw(EngineData &data)
{
}

SceneGame::SceneGame()
{
    addGameObject(new Camera());

    world = new World();

    addGameObject(world);

    Player *p = new Player();
    p->setPosition(Point(0, -100));
    addGameObject(p);
}

SceneGame::~SceneGame()
{
}

void SceneGame::init(EngineData &data)
{
    Player::getActive()->setPosition(Point(0, world->getGrassYAtXPosition(0, data) - 2)); // make sure player spawns on surface
}

bool SceneGame::onInput(EngineData &data)
{
    switch (data.getInput())
    {
    case 'e':
    case 'i':
        // open inventory
        data.setNextScene(L"Inventory");
        break;
    case 27: // escape
        // open pause menu
        data.setNextScene(L"Pause");
        break;
    default:
        return false;
    }

    return true;
}
