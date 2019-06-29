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
#include <openApp/Language/Operator.hpp>
#include <openApp/Language/Statement.hpp>

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
        ValueNode = 0,
        LocalNode,
        MemberNode,
        OperatorNode,
        StatementNode
    };

    /**
     * @brief Construct a new Expression Node object
     * 
     */
    ExpressionNode(void) : _data(Block) {}

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
    Variant<Var, String, ExpressionPtr, Operator, Statement> _data;
};