/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Path
*/

// stat
#include <sys/stat.h>
// std::filesystem
#include <filesystem>

#include <openApp/Core/Path.hpp>

bool oA::Path::Exists(const String &path)
{
    struct stat s;

    return !stat(path.c_str(), &s);
}

bool oA::Path::FileExists(const String &path)
{
    struct stat s;

    return !stat(path.c_str(), &s) && (s.st_mode & S_IFREG);
}

bool oA::Path::DirExists(const String &path)
{
    struct stat s;

    return !stat(path.c_str(), &s) && (s.st_mode & S_IFDIR);
}

oA::String oA::Path::GetAbsolutePath(const String &path)
{
    return std::filesystem::absolute(std::string(path)).c_str();
}

oA::String oA::Path::GetCanonicalPath(const String &path)
{
    return std::filesystem::canonical(std::string(path)).c_str();
}