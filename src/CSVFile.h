#ifndef __CSVFILE_H__
#define __CSVFILE_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>

#include "Object.h"

// Holds all data for CSV files.
class CSVFile
    : public Object
{
private:
    // the text from a file, broken into a list of a list of phrases (each cell is by itself)
    std::vector<std::vector<std::wstring>> data;

private:
    // reads all contents from the file at the file path into a wstring
    std::wstring getFileContents(const std::string &filePath);

public:
    CSVFile(const std::string &filePath);

    // gets the amount of lines (not including the header line, empty lines or comments)
    int getLineCount() const;

    // gets the line at the given index (not including the header line, empty lines or comments)
    std::vector<std::wstring> getLine(const int index) const;
};

#endif //__CSVFILE_H__
