#include "Selector.h"

Selector::Selector()
    : state(0)
{
    Sprite *sprite = new Sprite(1, 1);
    sprite->setDisplay(0, 0, getPixel());
    sprite->setColor(0, 0, 9); // selector color

    setSprite(sprite);
}

Selector::~Selector()
{
}

bool Selector::onUpdate(EngineData &data)
{
    state = (state + 1) % (STATES * STATE_SIZE);
    getSprite()->setDisplay(0, 0, getPixel());

    return true;
}

wchar_t Selector::getPixel() const
{
    // 1, 3/4, 1/2, 1/4, 0, 1/4, 1/2, 3/4
    switch (state / STATE_SIZE)
    {
    case 0:
        return Pixel::full;
    case 1:
    case 7:
        return Pixel::threeFourths;
    case 2:
    case 6:
        return Pixel::half;
    case 3:
    case 5:
        return Pixel::oneFourth;
    default:
        return Pixel::zero;
    }
}
