/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionNode
*/

#pragma once

#include <openApp/Types/Variant.hpp>
#include <openApp/Types/Memory.hpp>
#include <openApp/Core/Var.hpp>

namespace oA
{
    class ExpressionNode;
    class Expression;

    using ExpressionPtr = Shared<Expression>;
}

class oA::ExpressionNode
{
public:
    enum NodeType {
        OperatorNode = 0,
        ExprNode,
        ValueNode,
        DeclarationNode
    };

    /**
     * @brief Get internal Variant index
     *
     * @return NodeType Variant index
     */
    constexpr NodeType index(void) const noexcept { return static_cast<NodeType>(_data.index()); }

    /**
     * @brief Retreive the internal variant object
     *
     * @tparam T Type to extract
     * @return T& Internal object
     */
    template<typename T>
    T &getAs(void) { return std::get<T>(_data); }

private:
    Variant<ExpressionPtr, Var> _data;
};