#include "Sprite.h"

Sprite::~Sprite()
{
    if (display != nullptr)
    {
        delete[] display;
        delete[] colors;
    }
}

char Sprite::getDisplay(int const x, int const y) const
{
    return display[y * width + x];
}

unsigned short Sprite::getColor(int const x, int const y) const
{
    return colors[y * width + x];
}

void Sprite::setDisplay(int const x, int const y, wchar_t const d)
{
    display[y * width + x] = d;
}

void Sprite::setColor(int const x, int const y, unsigned short const c)
{
    colors[y * width + x] = c;
}

void Sprite::set(int const x, int const y, wchar_t const d, unsigned short const c)
{
    int index = y * width + x;
    display[index] = d;
    colors[index] = c;
}

void Sprite::set(int const index, wchar_t const d, unsigned short const c)
{
    display[index] = d;
    colors[index] = c;
}

void Sprite::print(int const x, int const y, Console &console) const
{
    int xx, yy, index;

    for (int row = 0; row < height; row++)
    {
        yy = y + row;

        if (yy < 0 || yy >= console.getHeight())
        {
            continue;
        }

        for (int col = 0; col < width; col++)
        {
            xx = x + col;

            if (xx < 0 || xx >= console.getWidth())
            {
                continue;
            }

            index = row * width + col;

            console.moveCursor(yy, xx);
            console.write(display[index], colors[index]);
        }
    }
}

Sprite::Sprite()
    : width(0), height(0), display(nullptr), colors(nullptr)
{
}

Sprite::Sprite(int const w, int const h)
    : width(w), height(h), display(new wchar_t[w * h]), colors(new unsigned short[w * h])
{
    // set display and colors to 0
    std::memset(display, 0, w * h * sizeof(wchar_t));
    std::memset(colors, 0, w * h * sizeof(unsigned short));
}

Sprite::Sprite(Sprite const &obj)
    : width(obj.width), height(obj.height), display(new wchar_t[obj.width * obj.height]), colors(new unsigned short[obj.width * obj.height])
{
    if (width > 0 && height > 0)
    {
        std::memcpy(display, obj.display, sizeof(wchar_t) * width * height);
        std::memcpy(colors, obj.colors, sizeof(unsigned short) * width * height);
    }
}

Sprite &Sprite::operator=(Sprite const &t)
{
    // make sure not self
    if (this != &t)
    {
        width = t.width;
        height = t.height;

        delete[] display;
        delete[] colors;

        display = new wchar_t[width * height];
        colors = new unsigned short[width * height];

        if (width > 0 && height > 0)
        {
            std::memcpy(display, t.display, sizeof(wchar_t) * width * height);
            std::memcpy(colors, t.colors, sizeof(unsigned short) * width * height);
        }
    }

    return *this;
}
