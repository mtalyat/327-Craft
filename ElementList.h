#ifndef __ELEMENTLIST_H__
#define __ELEMENTLIST_H__

#include <vector>
#include "Element.h"
#include "Event.h"

// A list UI Element that allows the user to navigate the items, and select one.
class ElementList
    : public Element
{
private:
    // The width of this list.
    int width;
    // The height of this list.
    int height;

    // The amount that has been scrolled.
    int scrollAmount;
    // The current index of the selected item.
    int index;

    // The amount the Y position must be adjused to print the list items.
    int adjustedY;
    // The amount the height must be adjusted to print the list items.
    int adjustedHeight;
    // The amount of adjustment for the printed list items.
    int adjustment;

    // The listed items, as strings.
    std::vector<std::wstring> *list;

    Event selectEvent;

private:
    int getMaxScroll() const;

protected:
    bool onInput(EngineData &data) override;
    void onEnter(EngineData &data) override;
    bool onUpdate(EngineData &data) override;
    void onDraw(EngineData &data) override;

public:
    ElementList(int const w, int const h);
    ~ElementList();

    void setList(std::vector<std::wstring> *newList);

    Event &onSelect() { return selectEvent; }

    void setIndex(int const i) { index = i; }
    int getIndex() const { return index; }
};

#endif // __ELEMENTLIST_H__