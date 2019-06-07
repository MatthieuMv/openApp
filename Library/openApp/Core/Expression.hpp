/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

#include <openApp/Containers/UMap.hpp>
#include <openApp/Core/ExpressionStack.hpp>
#include <openApp/Core/Property.hpp>

namespace oA { template<typename T> class Expression; }

/**
 * @brief This class extend Property to handle RPN expression computation
 *
 * @tparam T Internal Expression type
 */
template<typename T>
class oA::Expression : public Property<T>
{
public:
    using Property<T>::Property;

    /**
     * @brief Destroy the Expression object
     */
    virtual ~Expression(void) = default;

    /**
     * @brief Compute internal expression and set internal value to result
     *
     * @return true Internal value changed
     * @return false Internal value didn't changed
     */
    bool compute(void) {
        ExpressionStack<T> stack;
        if (_expr.empty())
            return false;
        for (auto &pair : _expr) {
            if (pair.second.isOperator())
                stack.processOperator(pair.second.getOperator());
            else
                stack.push(pair.second);
        }
        if (stack.empty())
            throw LogicError("Expression", "Non-null expression must have at least @1 return value@");
        return Property<T>::set(stack.pop().getValue());
    }

    /**
     * @brief A call will compute expression and always emit
     */
    void call(void) {
        if (!compute())
            this->emit();
    }

    /**
     * @brief Add a node to internal expression and add dependency if permited
     *
     * @param node Value to add
     */
    void addNode(ExpressionNode<T> &&node, bool addDependency = true) noexcept {
        Uint index = 0;
        if (addDependency && node.isExpression())
            index = depends(*node.getExpression());
        _expr.emplace_back(std::make_pair(index, std::move(node)));
    }

    /**
     * @brief Add dependency to a target Property
     *
     * @tparam U Target type
     * @param target Dependency
     * @return Uint Disconnect index
     */
    template<typename U>
    Uint depends(Property<U> &target) {
        return target.connect([this]{
            compute();
            return true;
        });
    }

    /**
     * @brief Add an expression event by move
     *
     * @param expr Expression to move
     * @return Uint Disconnect index
     */
    Uint connect(Expression<T> &&expr) {
        return connect([expr = std::move(expr)] {
            expr.call();
            return true;
        });
    }

    /**
     * @brief Clear internal expression
     */
    void clear(void) noexcept {
        _expr.clear();
    }

private:
    Vector<Pair<Uint, ExpressionNode<T>>> _expr;
};