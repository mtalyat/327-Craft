#ifndef __CSVOBJECT_H__
#define __CSVOBJECT_H__

#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <cstring>

#include "Object.h"

// Base class for all objects loaded from csv files.
class CSVObject
    : public Object
{
protected:
    int id;

protected:
    int stringToInt(const std::wstring &str) const;
    unsigned char stringToUnsignedChar(const std::wstring &str) const;
    bool stringToBool(const std::wstring &str) const;
    int *stringToIntArray(const std::wstring &str, int &length) const;
    unsigned char *stringToUnsignedCharArray(const std::wstring &str, int &length) const;

public:
    CSVObject();

    int getID() const { return id; }

    virtual void loadData(const std::vector<std::wstring> &lineData) = 0;
};

#endif //__CSVOBJECT_H__