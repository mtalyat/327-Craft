#include "ElementList.h"
ElementList::ElementList(int const w, int const h)
    : width(w), height(h), scrollAmount(0), index(0), adjustedY(0), adjustedHeight(0), adjustment(0), list(nullptr)
{
}

ElementList::~ElementList()
{
    if (list)
    {
        delete list;
    }
}

void ElementList::setList(std::vector<std::wstring> *newList)
{
    // if there is a list, delete it
    if (list && list != newList)
    {
        delete list;
    }

    list = newList;

    // adjust values for drawing
    if (list != nullptr && list->size() > (size_t)height)
    {
        // scrolling
        adjustedY = 1;
        adjustedHeight = height - 2;
        adjustment = -2;
    }
    else
    {
        // no scrolling
        adjustedY = 0;
        adjustedHeight = height;
        adjustment = 0;
    }

    // fix index
    if (!list)
    {
        setIndex(-1);
    }
    else if ((size_t)index >= list->size())
    {
        setIndex(list->size() - 1);
    }
}

bool ElementList::onInput(EngineData &data)
{
    if (!list || list->size() == 0)
    {
        // don't do anything without a list
        index = -1;
        return false;
    }

    switch (data.getInput())
    {
    case 'w': // up
        index = std::max(index - 1, 0);
        if (index - scrollAmount < 0)
        {
            scrollAmount = index;
        }
        break;
    case 's': // down
        index = std::min(index + 1, (int)list->size() - 1);
        if (index - scrollAmount >= adjustedHeight)
        {
            scrollAmount = index - (adjustedHeight - 1);
        }
        break;
    default:
        return false;
    }

    return true;
}

void ElementList::onEnter(EngineData &data)
{
    scrollAmount = 0;
    index = 0;

    focus();
}

bool ElementList::onUpdate(EngineData &data)
{
    return isFocused();
}

void ElementList::onDraw(EngineData &data)
{
    if (!list || list->size() == 0)
    {
        return;
    }

    Point position = getPosition();

    // draw from y to height or list size
    // use scroll to offset values
    for (size_t i = 0; i < (size_t)adjustedHeight && i < list->size() + adjustment; i++)
    {
        data.console.write(position.y + adjustedY + i, position.x + 2, list->at(i + scrollAmount));
    }

    // draw arrows if the user can scroll in a direction
    if (scrollAmount > 0)
    {
        // user can scroll up
        data.console.write(position.y, position.x, L"/\\");
    }

    if (scrollAmount < getMaxScroll())
    {
        // user can scroll down
        data.console.write(position.y + height - 1, position.x, L"\\/");
    }

    // now draw the "cursor"
    if (isFocused() && index >= 0 && index >= scrollAmount && index - scrollAmount < height)
    {
        data.console.write(position.y + adjustedY + index - scrollAmount, position.x, L">");
    }
}

int ElementList::getMaxScroll() const
{
    return list->size() - adjustedHeight;
}
