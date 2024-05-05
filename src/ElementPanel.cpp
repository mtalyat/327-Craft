#include "ElementPanel.h"

ElementPanel::ElementPanel(int const width, int const height, wchar_t const display, unsigned short const color)
{
    Sprite *sprite = new Sprite(width, height);

    // set all parts of the sprite to the panel data
    for (int i = 0; i < width * height; i++)
    {
        sprite->set(i, display, color);
    }

    setSprite(sprite);

    setColorCombo(color);
}
