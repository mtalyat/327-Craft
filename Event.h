#ifndef __EVENT_H__
#define __EVENT_H__

#include <vector>
#include <functional>
#include "Object.h"

// An Event is an object that can hold anonymous lambda functions that can be executed at a later time.
class Event : public Object
{
private:
    std::vector<std::function<void()>> functions;

public:
    Event();

    void addFunction(std::function<void()> func);

    Event &operator+=(std::function<void()> const &func);

    void invoke();
};

#endif // __EVENT_H__