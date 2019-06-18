/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** GetLine
*/

#include <openApp/Core/GetLine.hpp>

bool oA::GetLine(IStream &ss, String &line, char delim)
{
    Int i, max;

    if (!std::getline(ss, line, delim))
        return false;
    for (i = 0; std::isspace(line[i]); ++i);
    if (i)
        line.erase(0, i);
    max = line.length() - 1;
    for (i = max; i >= 0 && std::isspace(line[i]); --i);
    if (i != max)
        line.erase(i + 1);
    return true;
}