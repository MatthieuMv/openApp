/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Path
*/

#pragma once

#include <openApp/Types/String.hpp>

/**
 * @brief This namespace regroup every global path-related functions
 */
namespace oA::Path
{
    /**
     * @brief Check if path is either a file or a directory
     *
     * @param path Path to check
     * @return true Given path is either a file or a directory
     * @return false Given path doesn't exists
     */
    bool Exists(const String &path);

    /**
     * @brief Check if path is a file
     *
     * @param path Path to check
     * @return true Given path is a file
     * @return false Given path is not a file
     */
    bool FileExists(const String &path);

    /**
     * @brief Check if path is a directory
     *
     * @param path Path to check
     * @return true Given path is a directory
     * @return false Given path is not a directory
     */
    bool DirExists(const String &path);
}