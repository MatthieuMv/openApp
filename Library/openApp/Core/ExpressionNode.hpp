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

    /**
     * @brief Shared pointer to Expression
     *
     * @tparam T Type of Expression
     */
    template<typename T>
    using ExpressionPtr = Shared<Expression<T>>;
}

/**
 * @brief Expression node containing either an Operator, an Expression or a T value
 *
 * @tparam T Value type
 */
template<typename T>
class oA::ExpressionNode
{
    using NodeVariant = Variant<RPN::OperatorType, ExpressionPtr<T>, T>;

    static const oA::Int NodeOp = 0;
    static const oA::Int NodeExpr = 1;
    static const oA::Int NodeValue = 2;

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
    ExpressionNode(const ExpressionPtr<T> &property) : _var(property) {}

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
     * @brief Compare two ExpressionNode
     *
     * @param other To compare
     * @return bool True if nodes are equal
     */
    bool operator==(const ExpressionNode<T> &other) const noexcept { return _var == other._var; }

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
    bool isExpression(void) const noexcept { return _var.index() == NodeExpr; }

    /**
     * @brief Value check
     *
     * @return bool Check if ExpressionNode is a value (or an Expression containing a value)
     */
    bool isValue(void) const noexcept { return _var.index() == NodeValue || isExpression(); }

    /**
     * @brief Get the internal Operator object
     *
     * @return Operator Result
     */
    RPN::OperatorType getOperator(void) { return std::get<NodeOp>(_var); }


    /**
     * @brief Get the internal Expression object
     *
     * @return Expression Result
     */
    ExpressionPtr<T> &getExpression(void) { return std::get<NodeExpr>(_var); }

    /**
     * @brief Get the Value object (or Expression's value if possible)
     *
     * @return T& Result
     */
    const T &getValue(void) {
        if (isExpression())
            return getExpression()->get();
        return std::get<T>(_var);
    }

private:
    NodeVariant _var;
};