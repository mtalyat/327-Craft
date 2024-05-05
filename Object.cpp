#include "Object.h"
#include "string_converter.h"

std::string Object::toString() const
{
    return typeid(*this).name();
}

std::wstring Object::toWString() const
{
    return string_to_wstring(toString());
}
