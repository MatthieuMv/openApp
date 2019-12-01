/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#pragma once

#include <openApp/Core/Var.hpp>
#include <openApp/Language/ASTNode.hpp>

namespace oA
{
    class Property;

    using PropertyPtr = Shared<Property>;
}

/**
 * @brief This class extend Var to handle high level expression computation
 */
class oA::Property : public Var
{
public:
    /**
     * @brief Destroy the Property object
     */
    virtual ~Property(void) { clearTree(); }

    /**
     * @brief Construct a new Property object
     */
    Property(void) = default;

    /**
     * @brief Construct a new Property object
     *
     * @tparam T Type to instanciate Var with
     * @param value Value
     */
    template<typename T>
    explicit Property(T &&value) : Var(std::move(value)) {}

    /**
     * @brief Construct a new Property object by move
     *
     * @param other To move
     */
    Property(Property &&other) { swap(other); }

    /**
     * @brief Assign an Property value by move
     *
     * @param other To move
     * @return Property& Allow chain operators
     */
    Property &operator=(Property &&other);

    /**
     * @brief Copy a value
     *
     * @tparam T Type to copy
     * @param value Value to copy
     * @return Property& Allow chain operators
     */
    template<typename T>
    Property &operator=(T &&value) { Var::operator=(value); return *this; }

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
    void depends(const PropertyPtr &target);

    /**
     * @brief A call will compute expression and always emit
     */
    void call(void);

    /**
     * @brief Add an expression event by move, it will be computed at emit()
     *
     * @param expr Property to move
     * @return UInt Disconnect index
     */
    UInt connectEvent(PropertyPtr &&expr);

    /**
     * @brief Print to cout expression architecture
     *
     * @param tab Tabulation
     */
    void show(Int tab = 0) const noexcept;

    /**
     * @brief Returns true if Property has an internal AST tree
     *
     * @return true Property has tree
     * @return false  Property doesn't have tree
     */
    bool hasTree(void) const noexcept { return _tree.get(); }

    /**
     * @brief Set the Tree object. If the tree is const, this function will only set its compute value.
     *
     * @param tree Property AST tree
     */
    void setTree(Lang::ASTNodePtr &&tree);

    /**
     * @brief Clear internal tree, removing dependencies
     */
    void clearTree(void);

    /**
     * @brief Swap two expressions
     *
     * @param other Value to swap
     */
    void swap(Property &other);

    /**
     * @brief Bind this to an other property
     *
     * @param other Bind target
     */
    void bind(const PropertyPtr &other);

private:
    Lang::ASTNodePtr _tree;
    Vector<Pair<UInt, PropertyPtr>> _dependencies;
};