#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <locale.h>
#include <string>
#include <vector>
#include <ncurses.h>
#include "Object.h"

// https://www.vertex42.com/ExcelTips/unicode-symbols.html
enum Pixel
{
    full = L'█',
    threeFourths = L'▓',
    half = L'▒',
    oneFourth = L'░',
    zero = L' ',
    bottomLeft = L'▖',
    bottomRight = L'▗',
    topLeft = L'▘',
    topRight = L'▝',
    bottomLeftL = L'▜',
    bottomRightL = L'▛',
    topLeftL = L'▟',
    topRightL = L'▙',
    diagonalSlash = L'▞',
    diagonalBackSlash = L'▚',
    left = L'▌',
    right = L'▐',
    triangleUp = L'▲',
    triangleDown = L'▼',
    triangleLeft = L'◀',
    traingleRight = L'▶',
};

#define KEY_ESCAPE 27

// Provides an interface for easily printing content to the screen.
class Console : Object
{
private:
    int width, height;
    int cursorRow, cursorCol;
    int color;
    short colorComboIndex;

    static Console *active;

public:
    Console();
    ~Console();

    int getWidth() const;
    int getHeight() const;

    int getRow() const { return cursorRow; }
    int getCol() const { return cursorCol; }

    //  General Printing

    // Write the char to the console at the current cursor position.
    void write(const wchar_t c);

    // Writes the string to the console at the current cursor position.
    void write(const std::wstring &str);

    // Write the char to the console at the current cursor position with the given color.
    void write(const wchar_t c, const int colorCombo);

    // Writes the string to the console at the current cursor position with the given color.
    void write(const std::wstring &str, const int colorCombo);

    // Writes the string to the console at the current cursor position, and then moves to the next line.
    void writeLine(const std::wstring &str);

    // Writes the string to the console at the current cursor position with the given color, and then moves to the next line.
    void writeLine(const std::wstring &str, const int colorCombo);

    // Moves to the next line.
    void writeLine();

    // Moves the cursor to the given row and column.
    void moveCursor(const int row, const int col);

    // Writes the string to the console at the given row and column.
    void write(const int row, const int col, const std::wstring &str);

    // Writes the string to the console at the given row and column, with the given color.
    void write(const int row, const int col, const std::wstring &str, const int colorCombo);

    // Writes the string to the console at the given row and column, and then moves to the next line.
    void writeLine(const int row, const int col, const std::wstring &str);

    // Writes the string to the console at the given row and column with the given color, and then moves to the next line.
    void writeLine(const int row, const int col, const std::wstring &str, const int colorCombo);

    // Sets the color combo pair the console will be writing in.
    void setColorCombo(const int colorCombo);

    // Writes an error to the screen.
    void error(const std::wstring &str);

    // Clears the screen.
    void clearScreen() const;

    // Clears the screen, sets the color to default and sets the cursor position to (0, 0).
    void reset();

    // Refreshes (draws) the screen.
    void updateScreen() const { refresh(); }

    // Creates a new color combination for the Console, and returns its index.
    short createColorCombo(short fgColor, short bgColor);

    // Gets the active console
    static Console *getActive();

    // Sets the active console
    static void setActive(Console *console);
};

#endif