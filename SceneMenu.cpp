#include "SceneMenu.h"
#include "ElementManager.h"
#include "ElementText.h"
#include "ElementButton.h"
#include "ElementPanel.h"

SceneMenu::SceneMenu()
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::init(EngineData &data)
{
    // title
    ElementText *text = new ElementText(L"327 Craft");
    text->setPosition(Point(1, 1));
    addGameObject(text);

    // manager
    ElementManager *manager = new ElementManager();
    manager->focus();
    addGameObject(manager);

    EngineData *ed = &data;

    // manager -> buttons
    ElementManager::Node *playNode = new ElementManager::Node();
    playNode->element = new ElementButton(10, 3, L"Play", [ed]()
                                          { ed->setNextScene(L"Game"); });
    playNode->element->setParent(manager);
    playNode->element->setPosition(Point(35, 10));

    ElementManager::Node *quitNode = new ElementManager::Node();
    quitNode->element = new ElementButton(10, 3, L"Quit", [ed]()
                                          { ed->quit(); });
    quitNode->element->setParent(manager);
    quitNode->element->setPosition(Point(35, 14));

    playNode->below = quitNode;
    quitNode->above = playNode;

    manager->addNode(playNode);
    manager->addNode(quitNode);
}
