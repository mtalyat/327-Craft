#ifndef __ELEMENTBUTTON_H__
#define __ELEMENTBUTTON_H__

#include "Element.h"
#include "Event.h"

// A button UI Element that can trigger an Event when clicked.
class ElementButton
    : public Element
{
private:
    std::wstring text;
    Event clickEvent;

protected:
    bool onInput(EngineData &data) override;
    void onDraw(EngineData &data) override;

public:
    ElementButton();
    ElementButton(int const width, int const height, std::wstring const &str, unsigned short const colorId = 2);
    ElementButton(int const width, int const height, std::wstring const &str, std::function<void()> func, unsigned short const colorId = 2);
    ~ElementButton();

    Event &onClick() { return clickEvent; }
};

#endif // __ELEMENTBUTTON_H__