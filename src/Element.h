#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "GameObject.h"

// Base class for all UI GameObjects.
class Element
    : public GameObject
{
public:
    enum Anchor
    {
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

private:
    Anchor anchor;
    bool focused;
    unsigned short colorId;

public:
    Element();
    virtual ~Element() {}

    void setAnchor(Anchor a) { anchor = a; }

    void setFocused(bool const f) { focused = f; }
    void focus() { setFocused(true); }
    void unfocus() { setFocused(false); }
    bool isFocused() const { return focused; }

    void setColorCombo(unsigned short const id) { colorId = id; }

    bool input(EngineData &data) override;
    void draw(EngineData &data) override;
};

#endif // __ELEMENT_H__