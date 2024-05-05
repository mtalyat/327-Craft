#include "SceneInventory.h"
#include "ElementText.h"
#include "ElementPanel.h"
#include "ElementList.h"
#include "Player.h"
#include "Item.h"
#include <vector>

SceneInventory::SceneInventory()
    : lastListIndex(-1)
{
}

SceneInventory::~SceneInventory()
{
}

void SceneInventory::init(EngineData &data)
{
    unsigned short const color1 = 2;
    unsigned short const color2 = 1;

    ElementPanel *backPanel = new ElementPanel(80 - 2, 24 - 2, Pixel::half, color1);
    backPanel->setPosition(Point(1, 1));

    addGameObject(backPanel);

    ElementText *text = new ElementText(L"Inventory");
    text->setParent(backPanel, false);
    text->setColorCombo(color1);

    ElementPanel *frontPanel = new ElementPanel(80 - 6, 24 - 6, Pixel::zero, color2);
    frontPanel->setPosition(Point(2, 2));
    frontPanel->setParent(backPanel, false);

    list = new ElementList(80 - 6, 24 - 6);
    list->setParent(frontPanel, false);
    list->focus();

    nameText = new ElementText(L"Name: ");
    descriptionText = new ElementText(L"Desc: \"\"");
    amountText = new ElementText(L"Amnt: x0");
    typeText = new ElementText(L"Type: ");

    ElementText *itemTexts[] = {
        nameText, descriptionText, amountText, typeText};

    for (int i = 0; i < 4; i++)
    {
        itemTexts[i]->setPosition(Point(30, 4 + i));
        itemTexts[i]->setParent(frontPanel);
    }
}

bool SceneInventory::onInput(EngineData &data)
{
    switch (data.getInput())
    {
    case 'e':
    case 'i':
        // close inventory
        data.setNextScene(L"Game");
        break;
    default:
        return false;
    }

    return true;
}

void SceneInventory::onEnter(EngineData &data)
{
    // reset the data for the list on scene entry
    Player *player = Player::getActive();

    std::vector<std::wstring> *strings = new std::vector<std::wstring>();

    Inventory &inv = player->getInventory();
    Item *item;

    for (size_t i = 0; i < inv.size(); i++)
    {
        item = inv.get(i);

        strings->push_back(item->toWString());
    }

    list->setList(strings);
}

bool SceneInventory::onUpdate(EngineData &data)
{
    // display the data for the currently selected item
    int index = list->getIndex();

    if (index != lastListIndex)
    {
        lastListIndex = index;

        if (index == -1)
        {
            // no list
            nameText->setText(L"Name: ");
            descriptionText->setText(L"Desc: \"\"");
            amountText->setText(L"Amnt: x0");
            typeText->setText(L"Type: ");
            return false;
        }
        else
        {
            Player *player = Player::getActive();
            Inventory &inv = player->getInventory();

            // find the selected item and get its data
            Item *item = inv.get(index);
            ItemData *itemData = data.getItem(item->getID());

            // update stats
            nameText->setText(L"Name: " + itemData->getName());
            descriptionText->setText(L"Desc: \"" + itemData->getDescription() + L'"');
            amountText->setText(L"Amnt: x" + std::to_wstring(item->getAmount()));
            typeText->setText(L"Type: " + itemData->getBlockID() == 0 ? L"Item " : L"Block");
            return true;
        }
    }

    return false;
}
