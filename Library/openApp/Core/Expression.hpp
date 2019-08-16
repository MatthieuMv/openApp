/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

#include <openApp/Core/Property.hpp>
#include <openApp/Core/Var.hpp>
#include <openApp/Language/ASTNode.hpp>

namespace oA
{
    class Expression;

    using ExpressionPtr = Shared<Expression>;
}

/**
 * @brief This class extend Property to handle high level expression computation
 * Expression only uses Var as internal variable
 */
class oA::Expression : public Property<Var>
{
public:
    using Property<Var>::Property;
    using Property<Var>::operator=;

    /**
     * @brief Destroy the Expression object
     */
    virtual ~Expression(void) { clearTree(); }

    /**
     * @brief Construct a new Expression object by move
     *
     * @param other To move
     */
    Expression(Expression &&other) { swap(other); }

    /**
     * @brief Assign an Expression value by move
     *
     * @param other To move
     * @return Expression& Allow chain operators
     */
    Expression &operator=(Expression &&other);

    /**
     * @brief Compute internal expression and set internal value to result
     *
     * @return true Internal value changed
     * @return false Internal value didn't changed
     */
    bool compute(void);

    /**
     * @brief Add dependency of internal expression
     *
     * @param target Dependency
     */
    void depends(Expression &target) {
        _dependencies.emplace_back(std::make_pair(
            target.connect([this]{
                compute();
                return true;
            }),
            &target
        ));
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
    Uint connectEvent(ExpressionPtr &&expr);

    /**
     * @brief Print to cout expression architecture
     *
     * @param tab Tabulation
     */
    void show(Int tab = 0) const noexcept;

    /**
     * @brief Set the Tree object. If the tree is const, this function will only set its compute value.
     *
     * @param tree Expression AST tree
     */
    void setTree(Lang::ASTNodePtr &&tree) {
        if (_tree)
            clearTree();
        if (!tree)
            throw LogicError("Expression", "Can't set null expression @tree@");
        else if (tree->isConst())
            set(tree->compute());
        else
            _tree = std::move(tree);
    }

    /**
     * @brief Clear internal tree, removing dependencies
     */
    void clearTree(void) {
        _dependencies.apply([](auto &pair) { pair.second->disconnect(pair.first); });
        _dependencies.clear();
        _tree.reset();
    }

    /**
     * @brief Swap two expressions
     *
     * @param other Value to swap
     */
    void swap(Expression &other) {
        Property<Var>::swap(other);
        _tree.swap(other._tree);
    }

private:
    Lang::ASTNodePtr _tree;
    Vector<Pair<Uint, Expression *>> _dependencies;
};