/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** OANode
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>

namespace oA::Lang { struct OANode; }

struct oA::Lang::OANode
{
    enum Type {
        RootNode,
        ImportNode,
        ItemNode,
        AssignNode,
        PropertyNode,
        FunctionNode,
        EventNode
    };

    Vector<String> args;
    Vector<OANode> childs;
    Type type = RootNode;
};