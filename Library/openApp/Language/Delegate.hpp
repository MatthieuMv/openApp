/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Delegate
*/

#pragma once

#include <openApp/Language/Instantiator.hpp>

namespace oA::Lang
{
    class Delegate;
}

/**
 * @brief This class cache an Instantiator in order to use it later instancing a delegated child
 */
class oA::Lang::Delegate : protected Instantiator
{
public:
    /**
     * @brief Construct a new Delegate object
     *
     * @param verbose Activates or not Instantiator's verbose
     */
    Delegate(const oA::String &path, bool verbose = false);

    /**
     * @brief Destroy the Delegate object
     */
    virtual ~Delegate(void) = default;

    /**
     * @brief Instantiate a new child in root
     *
     * @param root Root Item
     * @return Item& Appened item
     */
    Item &instantiate(const ItemPtr &root);

private:
    oA::String _path;
};