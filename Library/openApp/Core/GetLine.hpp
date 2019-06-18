/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** GetLine
*/

#pragma once

#include <openApp/Types/Stream.hpp>
#include <openApp/Types/String.hpp>

namespace oA
{
    /**
     * @brief Retreive a line from a stream, croping useless spaces
     *
     * @param ss Stream to extract
     * @param line Target String
     * @param delim Line delimiter
     * @return true Extract succeed
     * @return false Extract failed
     */
    bool GetLine(IStream &ss, String &line, char delim = '\n');
};