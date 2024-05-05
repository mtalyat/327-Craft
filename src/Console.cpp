#include "Console.h"

Console *Console::active = nullptr;

Console::Console()
    : width(0), height(0), cursorRow(0), cursorCol(0), color(0), colorComboIndex(1)
{
    // for unicode
    setlocale(LC_ALL, "");

    // initialize curses mode
    initscr();

    cursorRow = 0;
    cursorCol = 0;
    color = -1;

    // get console size
    getmaxyx(stdscr, height, width);

    // raw data, so esc is an integer instead of 3 chars
    raw();

    // hide character input
    noecho();

    // let user enter one character at a time
    cbreak();

    // hide cursor
    curs_set(0);

    //
    keypad(stdscr, TRUE);

    // do not block the program
    nodelay(stdscr, 1);

    // initialize all colors for ncurses after this
    start_color();

    if (active == nullptr)
    {
        active = this;
    }
}

Console::~Console()
{
    // return back to normal input
    echo();
    nocbreak();
}

int Console::getWidth() const
{
    return width;
}

int Console::getHeight() const
{
    return height;
}

void Console::write(const wchar_t c)
{
    printw("%lc", c);
    cursorCol++;

    if (cursorCol >= width)
    {
        cursorCol -= width;
        cursorRow++;
    }
}

void Console::write(const std::wstring &str)
{
    printw("%ls", str.c_str());
    cursorCol += str.length();

    // if col position is over the width, drop to next line
    while (cursorCol >= width)
    {
        cursorCol -= width;
        cursorRow++;
    }
}

void Console::write(const std::wstring &str, const int colorCombo)
{
    setColorCombo(colorCombo);
    write(str);
}

void Console::writeLine(const std::wstring &str)
{
    write(str);
    moveCursor(cursorRow + 1, 0);
}

void Console::writeLine(const std::wstring &str, const int colorCombo)
{
    write(str, colorCombo);
    moveCursor(cursorRow + 1, 0);
}

void Console::moveCursor(const int row, const int col)
{
    cursorRow = row;
    cursorCol = col;

    move(row, col);
}

void Console::write(const int row, const int col, const std::wstring &str)
{
    moveCursor(row, col);
    write(str);
}

void Console::write(const int row, const int col, const std::wstring &str, const int colorCombo)
{
    moveCursor(row, col);
    write(str, colorCombo);
}

void Console::write(const wchar_t c, const int colorCombo)
{
    setColorCombo(colorCombo);
    write(c);
}

void Console::writeLine(const int row, const int col, const std::wstring &str)
{
    moveCursor(row, col);
    writeLine(str);
}

void Console::writeLine(const int row, const int col, const std::wstring &str, const int colorCombo)
{
    moveCursor(row, col);
    writeLine(str, colorCombo);
}

void Console::writeLine()
{
    moveCursor(cursorRow + 1, 0);
}

void Console::setColorCombo(const int colorCombo)
{
    // disable the last color, if there was one
    if (color < 0)
    {
        attroff(COLOR_PAIR(color));
    }

    // set the new color
    color = colorCombo;

    // enable the new color
    if (color >= 0)
    {
        attron(COLOR_PAIR(color));
    }
}

void Console::error(const std::wstring &str)
{
    write(0, 0, L"ERROR: ", 0);
    write(str);
}

void Console::clearScreen() const
{
    clear();
}

void Console::reset()
{
    setColorCombo(0);
    clearScreen();
    moveCursor(0, 0);
}

short Console::createColorCombo(short fgColor, short bgColor)
{
    init_pair(colorComboIndex, fgColor, bgColor);

    // return the current value, then increment
    return colorComboIndex++;
}

Console *Console::getActive()
{
    return active;
}

void Console::setActive(Console *console)
{
    active = console;
}
