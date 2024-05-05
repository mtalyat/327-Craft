#include "CSVFile.h"

std::wstring CSVFile::getFileContents(const std::string &filePath)
{
    // open file
    std::wifstream file(filePath, std::ios::binary);

    // make sure file was opened
    if (!file)
    {
        return L"";
    }

    // https://stackoverflow.com/questions/4775437/read-unicode-utf-8-file-into-wstring
    // getting this to work was a pain in the ass
    file.imbue(std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>()));
    std::wstringstream wss;
    wss << file.rdbuf();
    return wss.str();
}

CSVFile::CSVFile(const std::string &filePath)
{
    std::wstring contents = getFileContents(filePath);

    std::wstringstream ss(contents);
    std::vector<std::wstring> items;
    std::wstring line;
    std::wstring phrase;
    wchar_t c;
    size_t length;
    size_t i;

    // skip first line, which is just the names that we don't care about since we are manually assigning data
    std::getline(ss, line);

    // go through the lines
    while (std::getline(ss, line))
    {
        length = line.length();

        // if there is no text on this line, OR
        // if there is a # (comment) on this line, skip it
        if (length == 0 || line.at(0) == L'#')
        {
            continue;
        }

        // go through each data object in the line
        for (i = 0; i < length; i++)
        {
            c = line.at(i);

            if (c == L',')
            {
                if (phrase.length() == 0)
                {
                    items.push_back(L"-1");
                }
                else
                {
                    items.push_back(phrase);
                }
                phrase = L"";
            }
            else
            {
                phrase += c;
            }
        }

        if (phrase.length() > 0)
        {
            items.push_back(phrase);
            phrase = L"";
        }
        else
        {
            items.push_back(L"-1");
        }

        data.push_back(items);
        items.clear();
    }
}

int CSVFile::getLineCount() const
{
    return data.size();
}

std::vector<std::wstring> CSVFile::getLine(const int index) const
{
    return data.at(index);
}