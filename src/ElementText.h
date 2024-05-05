#ifndef __ELEMENTTEXT_H__
#define __ELEMENTTEXT_H__

#include <string>
#include "Element.h"

// A UI Element that displays a wstring.
class ElementText
    : public Element
{
public:
    std::wstring text;

protected:
    void onDraw(EngineData &data) override;

public:
    ElementText();
    ElementText(std::wstring const &str);
    ~ElementText();

    void setText(std::wstring const &str);
    std::wstring const &getText() const { return text; }
};

#endif // __ELEMENTTEXT_H__