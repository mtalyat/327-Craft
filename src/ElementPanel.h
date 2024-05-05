#ifndef __ELEMENTPANEL_H__
#define __ELEMENTPANEL_H__

#include "Element.h"
#include "Console.h"

// A panel UI element (just a 2D box on the screen that has all the same characters/colors throughout).
class ElementPanel
    : public Element
{
public:
    ElementPanel(int const width, int const height, wchar_t const display = Pixel::zero, unsigned short const color = 1);
    ~ElementPanel() {}
};

#endif // __ELEMENTPANEL_H__