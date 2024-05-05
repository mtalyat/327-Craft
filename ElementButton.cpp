#include "ElementButton.h"
#include "string_converter.h"

ElementButton::~ElementButton()
{
}

ElementButton::ElementButton()
    : text()
{
}

ElementButton::ElementButton(int const width, int const height, std::wstring const &str, unsigned short const colorId)
    : text(str)
{
    Sprite *sprite = new Sprite(width, height);

    for (int i = 0; i < width * height; i++)
    {
        sprite->set(i, ' ', colorId);
    }

    setSprite(sprite);

    setColorCombo(colorId);
}

ElementButton::ElementButton(int const width, int const height, std::wstring const &str, std::function<void()> func, unsigned short const colorId)
    : ElementButton(width, height, str, colorId)
{
    clickEvent.addFunction(func);
}

void ElementButton::onDraw(EngineData &data)
{
    // sprite is already drawn, draw text over it, centered
    Sprite *sprite = getSprite();

    int width = 0;
    int height = 0;
    if (sprite)
    {
        width = sprite->getWidth();
        height = sprite->getHeight();
    }
    Point pos = getPosition();

    std::wstring textToDraw = text;
    // if focused, show it
    if (isFocused())
    {
        textToDraw = L"> " + text + L" <";
    }

    int y = pos.y + height / 2;
    int x = pos.x + width / 2 - textToDraw.size() / 2;

    data.console.write(y, x, textToDraw);
}

bool ElementButton::onInput(EngineData &data)
{
    switch (data.getInput())
    {
    case ' ':
    case '\n':
    case '5':
        clickEvent.invoke();
        break;
    default:
        return false;
    }

    return true;
}
