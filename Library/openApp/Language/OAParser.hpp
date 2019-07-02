/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OAParser
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/App/Item.hpp>
#include <openApp/Language/OANode.hpp>

namespace oA::Lang { class OAParser; }

class oA::Lang::OAParser
{
public:
    /**
     * @brief Parse file content and return an Item as result
     * 
     * @param path File path
     * @return ItemPtr Root Item instancied from file
     */
    static ItemPtr ProcessFile(const String &path);

    /**
     * @brief Parse string content and return an Item as result
     * 
     * @param path File string
     * @return ItemPtr Root Item instancied from string
     */
    static ItemPtr ProcessString(const String &string);
    
private:
};