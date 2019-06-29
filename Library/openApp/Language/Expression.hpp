/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

#include <openApp/Core/Property.hpp>
#include <openApp/Language/Tree.hpp>
#include <openApp/Language/ExpressionNode.hpp>

namespace oA { class Expression; }

/**
 * @brief This class extend Property to handle high level expression computation
 * Expression only uses Var as internal variable
 */
class oA::Expression : public Property<Var>
{
public:
    using Property<Var>::Property;

    /**
     * @brief Destroy the Expression object
     */
    virtual ~Expression(void) = default;

    /**
     * @brief Add dependency to a target Property
     *
     * @param target Dependency
     * @return Uint Disconnect index
     */
    template<typename T>
    Uint depends(Property<T> &target) {
        return target.connect([this]{
            compute();
            return true;
        });
    }

    /**
     * @brief A call will compute expression and always emit
     */
    void call(void);

    /**
     * @brief Add an expression event by move, it will be computed at emit()
     *
     * @param expr Expression to move
     * @return Uint Disconnect index
     */
    Uint connectEvent(Expression &&expr) noexcept;

    /**
     * @brief Set the internal Tree object
     *
     * @param tree Tree to set
     */
    void setExpressionTree(Tree<ExpressionNode> &&tree);

private:
    Tree<ExpressionNode> _tree;

    /**
     * @brief Compute internal expression and set internal value to result
     *
     * @return true Internal value changed
     * @return false Internal value didn't changed
     */
    bool compute(void);
};