/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ASTNode
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Core/Var.hpp>

namespace oA::Lang
{
    class ASTNode;

    class ASTNodeList;

    using ASTNodePtr = Unique<ASTNode>;
}

/**
 * @brief Base class for every openApp language node
 */
struct oA::Lang::ASTNode
{
    /**
     * @brief Internal type of the node
     */
    enum NodeType {
        Root,
        Import,
        Class,
        Declaration,
        Group,
        ExpressionGroup,
        Reference,
        Local,
        Value,
        Operator,
        Statement
    };

    /**
     * @brief Signal used on return statement
     */
    struct ReturnSignal
    {
        ReturnSignal(Var &&var) : value(std::move(var)) {}

        Var value;
    };

    /**
     * @brief Signal used on loop break
     */
    struct BreakSignal {};

    /**
     * @brief List of children nodes
     */
    Vector<ASTNodePtr> children;

    /**
     * @brief Show internal node tree
     *
     * @param root Root node
     * @param tab Actual indentation (used in recursion)
     */
    static void ShowTree(const ASTNode &root, Int tab = 0);

    /**
     * @brief Destroy the ASTNode object
     */
    virtual ~ASTNode(void) = default;

    /**
     * @brief Get the Type object
     *
     * @return NodeType Internal type
     */
    virtual NodeType getType(void) const { return Root; }

    /**
     * @brief Compute if possible internal node
     *
     * @return Var Resulting variable
     */
    virtual Var compute(void) { throw LogicError("ASTNode", "Can't compute uncomputable node"); }

    /**
     * @brief Emplace an existing node
     *
     * @param node Node to move
     */
    void emplace(ASTNodePtr &&node) { children.emplace_back(std::move(node)); }

    /**
     * @brief Construct a new node
     *
     * @tparam NodeType Type of constructed node
     * @tparam Args Type of constructor arguments
     * @param args Constructor arguments
     * @return NodeType& Resulting node
     */
    template<typename NodeType, typename ...Args>
    NodeType &emplaceAs(Args &&...args) { return dynamic_cast<NodeType &>(*children.emplace_back(std::make_unique<NodeType>(std::forward<Args>(args)...))); }
};