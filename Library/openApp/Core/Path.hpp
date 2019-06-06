/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Path
*/

#pragma once

#include <openApp/Types/String.hpp>

namespace oA::Path
{
    // Check if path is either a file or a directory
    bool Exists(const String &path);

    // Check if path is a file
    bool FileExists(const String &path);

    // CHeck if path is a directory
    bool DirExists(const String &path);
}