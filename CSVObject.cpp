#include "CSVObject.h"

int CSVObject::stringToInt(const std::wstring &str) const
{
    return std::stoi(str);
}

unsigned char CSVObject::stringToUnsignedChar(const std::wstring &str) const
{
    int i = stringToInt(str);
    return (unsigned char)(i == -1 ? 255 : i); // 255 is invalid block
}

bool CSVObject::stringToBool(const std::wstring &str) const
{
    return stringToInt(str) != 0;
}

int *CSVObject::stringToIntArray(const std::wstring &str, int &length) const
{
    // make sure brackets at the beginning and ends
    if (str.at(0) != L'[' || str.at(str.size() - 1) != L']')
    {
        length = 0;
        return nullptr;
    }

    // we know 0 and size-1 are [ and ], so... if size == 2, then it is empty
    if (str.size() <= 2)
    {
        length = 0;
        return new int[0];
    }

    // temporarily store in a vector since the size is unknown
    std::vector<int> ints;

    std::wstring substr = L"";

    for (size_t i = 1; i < str.size(); i++)
    {
        if (str.at(i) == L'|' || str.at(i) == L']')
        {
            // if a separator, add the current substring
            if (substr.size() > 0)
            {
                ints.push_back(stringToInt(substr));
                substr = L"";
            }
        }
        else
        {
            // add to substring
            substr += str.at(i);
        }
    }

    // return array of ints
    length = ints.size();
    int *intArr = new int[length];

    // std::copy(ints.begin(), ints.end(), intArr);
    std::memcpy(intArr, &ints.at(0), sizeof(int) * length);

    return intArr;
}

unsigned char *CSVObject::stringToUnsignedCharArray(const std::wstring &str, int &length) const
{
    // make sure brackets at the beginning and ends
    if (str.at(0) != L'[' || str.at(str.size() - 1) != L']')
    {
        length = 0;
        return nullptr;
    }

    // we know 0 and size-1 are [ and ], so... if size == 2, then it is empty
    if (str.size() <= 2)
    {
        length = 0;
        return new unsigned char[0];
    }

    // temporarily store in a vector since the size is unknown
    std::vector<unsigned char> chars;

    std::wstring substr = L"";

    for (size_t i = 1; i < str.size(); i++)
    {
        if (str.at(i) == L'|' || str.at(i) == L']')
        {
            // if a separator, add the current substring
            if (substr.size() > 0)
            {
                chars.push_back(stringToInt(substr));
                substr = L"";
            }
        }
        else
        {
            // add to substring
            substr += str.at(i);
        }
    }

    // return array of ints
    length = chars.size();
    unsigned char *arr = new unsigned char[length];

    // std::copy(chars.begin(), chars.end(), arr);
    // copy over
    std::memcpy(arr, &chars.at(0), sizeof(unsigned char) * length);

    return arr;
}

CSVObject::CSVObject()
    : id(0)
{
}