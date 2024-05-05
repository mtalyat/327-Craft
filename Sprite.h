#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <cstring>
#include "Object.h"
#include "Console.h"

// A text-based "bitmap" containing a 2D grid of data for characters, as well as color combinations.
class Sprite
    : public Object
{
private:
    int width;
    int height;
    wchar_t *display;
    unsigned short *colors;

public:
    Sprite();
    Sprite(int const w, int const h);
    ~Sprite();

    // copy constructor
    Sprite(Sprite const &obj);
    // assignment operator
    Sprite &operator=(Sprite const &t);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    char getDisplay(int const x, int const y) const;
    unsigned short getColor(int const x, int const y) const;

    void setDisplay(int const x, int const y, wchar_t const d);
    void setColor(int const x, int const y, unsigned short const c);
    void set(int const x, int const y, wchar_t const d, unsigned short const c);
    void set(int const index, wchar_t const d, unsigned short const c);

    void print(int const x, int const y, Console &console) const;
};

#endif // __SPRITE_H__