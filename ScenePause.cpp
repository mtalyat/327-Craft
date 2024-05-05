#include "ScenePause.h"
#include "ElementManager.h"
#include "ElementPanel.h"
#include "ElementButton.h"
#include "ElementText.h"

void ScenePause::init(EngineData &data)
{
    ElementPanel *panel = new ElementPanel(12, 11, Pixel::half, 2);
    panel->setPosition(Point(data.console.getWidth() / 2 - 6, data.console.getHeight() / 2 - 6));
    addGameObject(panel);

    ElementText *text = new ElementText(L"Paused");
    text->setParent(panel);
    text->setLocalPosition(Point(1, 1));

    manager = new ElementManager();
    manager->setParent(panel);
    manager->setLocalPosition(Point());

    EngineData *ed = &data;

    ElementManager::Node *resumeNode = new ElementManager::Node();
    resumeNode->element = new ElementButton(
        10, 3, L"Resume", [ed]()
        { ed->setNextScene(L"Game"); });
    resumeNode->element->setParent(manager);
    resumeNode->element->setLocalPosition(Point(1, 3));

    ElementManager::Node *menuNode = new ElementManager::Node();
    menuNode->element = new ElementButton(
        10, 3, L"Menu", [ed]()
        { ed->setNextScene(L"Menu"); });
    resumeNode->element->setParent(manager);
    resumeNode->element->setLocalPosition(Point(1, 7));

    resumeNode->below = menuNode;
    menuNode->above = resumeNode;

    manager->addNode(resumeNode);
    manager->addNode(menuNode);
}

void ScenePause::onEnter(EngineData &data)
{
    if (manager)
    {
        manager->setCurrent(0);
    }
}

ScenePause::ScenePause()
    : manager(nullptr)
{
}

bool ScenePause::onInput(EngineData &data)
{
    switch (data.getInput())
    {
    case 27: // escape
        data.setNextScene(L"Game");
        break;
    default:
        return false;
    }

    return true;
}
