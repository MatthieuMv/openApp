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

namespace oA
{
    template<typename T>
    class Expression;
}

/**
 * @brief This class extend Property to handle high level RPN expression computation
 *
 * Expression uses a container of nodes which composes its inernal RPN expression
 * To be computed, Expression uses an ExpressionNode which provides an abstract operator processing function
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
        if (stack.size() != 1)
            throw LogicError("Expression", "Non-null expression must have @1 return value@");
        return Property<T>::set(stack.popValue());
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
        auto &n = _expr.emplace_back(std::make_pair(0, std::move(node)));
        if (!addDependency || !n.second.isExpression())
            return;
        for (auto &p : _expr) {
            if (p.first && p.second == n.second)
                return;
        }
        n.first = depends(*n.second.getExpression());
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
     * @brief Add an expression event by move, it will be computed at emit()
     *
     * @param expr Expression to move
     * @return Uint Disconnect index
     */
    Uint connectEvent(Expression<T> &&expr) noexcept {
        return this->connect([event = std::move(expr)](void) mutable {
            event.call();
            return true;
        });
    }

    /**
     * @brief Reset internal expression
     */
    virtual void clearExpression(void) noexcept {
        _expr.apply([](auto &p) {
            if (p.first && p.second.isExpression())
                p.second.getExpression()->disconnect(p.first);
        });
        _expr.clear();
    }

private:
    Vector<Pair<Uint, ExpressionNode<T>>> _expr;
};