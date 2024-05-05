#include "Event.h"

Event::Event()
{
}

void Event::addFunction(std::function<void()> func)
{
    functions.push_back(func);
}

Event &Event::operator+=(std::function<void()> const &func)
{
    addFunction(func);

    return *this;
}

void Event::invoke()
{
    for (size_t i = 0; i < functions.size(); i++)
    {
        functions[i]();
    }
}
