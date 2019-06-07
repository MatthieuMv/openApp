/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionNode
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/Variant.hpp>
#include <openApp/Core/Operator.hpp>

namespace oA
{
    template<typename T> class Expression;
    template<typename T> class ExpressionNode;
}

/**
 * @brief Expression node containing either an Operator, an Expression or a T value
 *
 * @tparam T Value type
 */
template<typename T>
class oA::ExpressionNode
{
    using NodeVariant = Variant<RPN::OperatorType, Shared<Expression<T>>, T>;

public:
    /**
     * @brief Construct a new Expression Node object by operator
     *
     * @param op Node operator
     */
    ExpressionNode(RPN::OperatorType op) : _var(op) {}

    /**
     * @brief Construct a new Expression Node object by shared property
     *
     * @param property Shared property
     */
    ExpressionNode(const Shared<Expression<T>> &property) : _var(property) {}

    /**
     * @brief Construct a new Expression Node object by value copy
     *
     * @param value Value to copy
     */
    ExpressionNode(const T &value) : _var(value) {}

    /**
     * @brief Construct a new Expression Node object by copy
     *
     * @param other Value to copy
     */
    ExpressionNode(const ExpressionNode<T> &other) = default;

    /**
     * @brief Construct a new Expression Node object by move
     *
     * @param other Value to move
     */
    ExpressionNode(ExpressionNode<T> &&other) = default;

    /**
     * @brief Operator check
     *
     * @return bool Check if ExpressionNode is an Operator
     */
    bool isOperator(void) const noexcept { return _var.index() == 0; }

    /**
     * @brief Expression check
     *
     * @return bool Check if ExpressionNode is a Expression
     */
    bool isExpression(void) const noexcept { return _var.index() == 1; }

    /**
     * @brief Value check
     *
     * @return bool Check if ExpressionNode is a value
     */
    bool isValue(void) const noexcept { return _var.index() == 2; }

    /**
     * @brief Get the internal Operator object
     *
     * @return Operator Result
     */
    RPN::OperatorType getOperator(void) { return Get<RPN::OperatorType>(_var); }


    /**
     * @brief Get the internal Expression object
     *
     * @return Expression Result
     */
    Shared<Expression<T>> getExpression(void) { return Get<Shared<Expression<T>>>(_var); }

    /**
     * @brief Get the Value object (or Expression's value if possible)
     *
     * @return T& Result
     */
    const T &getValue(void) {
        if (isExpression())
            return getExpression()->get();
        return Get<T>(_var);
    }

private:
    NodeVariant _var;
};