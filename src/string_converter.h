#ifndef __STRING_CONVERTER_H__
#define __STRING_CONVERTER_H__

#include <locale>
#include <codecvt>
#include <string>

// Special thanks to this post:
// https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t

// Converts a wstring to a string
std::string wstring_to_string(std::wstring const &str);

// Converts a string to a wstring
std::wstring string_to_wstring(std::string const &str);

#endif // __STRING_CONVERTER_H__