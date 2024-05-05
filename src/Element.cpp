#include "Element.h"
void Element::draw(EngineData &data)
{
    // do not draw based on camera pos, base it off of screen and anchors
    Sprite *sprite = getSprite();
    if (sprite)
    {
        Point position = getPosition();
        sprite->print(position.x, position.y, data.console);
    }

    // set back to color...
    data.console.setColorCombo(colorId);

    // draw self
    onDraw(data);

    // draw children
    GameObject *child;
    for (size_t i = 0; i < getChildCount(); i++)
    {
        child = getChild(i);

        if (child->getEnabled())
        {
            child->draw(data);
        }
    }
}

Element::Element()
    : anchor(Element::Anchor::TopLeft), focused(false), colorId(1)
{
}

bool Element::input(EngineData &data)
{
    bool input;
    if (focused)
    {
        // only do input events if focused
        input = onInput(data);
    }

    // children
    GameObject *child;
    for (size_t i = 0; i < getChildCount(); i++)
    {
        child = getChild(i);

        if (child->getEnabled())
        {
            input = child->input(data) || input;
        }
    }

    return input;
}
