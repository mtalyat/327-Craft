#include "ElementText.h"

void ElementText::onDraw(EngineData &data)
{
    // draw the string at the position
    Point positon = getPosition();
    data.console.write(positon.y, positon.x, text);
}

ElementText::ElementText()
    : text(L"")
{
}

ElementText::ElementText(std::wstring const &str)
    : text(str)
{
}

ElementText::~ElementText()
{
}

void ElementText::setText(std::wstring const &str)
{
    text = str;
}
