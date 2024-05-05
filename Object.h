#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

// The base class for all classes.
class Object
{
public:
    Object() {}
    virtual ~Object() {}

    virtual std::string toString() const;
    virtual std::wstring toWString() const;
};

#endif // __OBJECT_H__