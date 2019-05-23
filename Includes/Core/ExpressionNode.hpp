/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ExpressionNode
*/

#pragma once

// Property
#include "Core/Property.hpp"
// Operator
#include "Core/Operators.hpp"
// Variant
#include "Core/Variant.hpp"

namespace oA
{
    enum NodeType {
        NodeOperator = 0,
        NodeValue,
        NodeExpression
    };

    template<typename T>
    class Expression;

    template<typename U>
    using ExpressionPtr = oA::Shared<Expression<U>>;

    template<typename T>
    class ExpressionNode;
}

template<typename T>
class oA::ExpressionNode
{
public:
    ExpressionNode(void) = default;
    ExpressionNode(const OperatorType &opType) : _data(opType) {}
    ExpressionNode(const T &value) : _data(value) {}
    ExpressionNode(const ExpressionPtr<T> &property) : _data(property) {}

    NodeType index(void) const noexcept { return static_cast<NodeType>(_data.index()); }

    bool isOperator(void) const noexcept { return index() == NodeOperator; }
    bool isValue(void) const noexcept { return index() == NodeValue; }
    bool isExpression(void) const noexcept { return index() == NodeExpression; }
    bool isOperand(void) const noexcept { return isValue() || isExpression(); }

    OperatorType getOperator(void) {
        if (!isOperator())
            throw AccessError("ExpressionNode", "Node is not an operator");
        return std::get<OperatorType>(_data);
    }

    T &getValue(void) {
        if (isExpression())
            return getExpression()->get();
        if (!isValue())
            throw AccessError("ExpressionNode", "Node is not a value");
        return std::get<T>(_data);
    }

    ExpressionPtr<T> &getExpression(void) {
        if (!isExpression())
            throw AccessError("ExpressionNode", "Node is not an expression");
        return std::get<ExpressionPtr<T>>(_data);
    }

private:
    Variant<OperatorType, T, ExpressionPtr<T>> _data;
};