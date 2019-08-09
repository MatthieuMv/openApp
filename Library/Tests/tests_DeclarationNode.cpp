/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_DeclarationNode
*/

#include <criterion/criterion.h>
#include <openApp/Language/Nodes/DeclarationNode.hpp>

Test(DeclarationNode, Symbols)
{
    oA::Lang::DeclarationNode node("Name", oA::Lang::DeclarationNode::AssignmentDeclaration);

    cr_assert_eq(node.getDeclarationSymbol(), "Assignment");

    node.type = oA::Lang::DeclarationNode::PropertyDeclaration;
    cr_assert_eq(node.getDeclarationSymbol(), "Property");

    node.type = oA::Lang::DeclarationNode::FunctionDeclaration;
    cr_assert_eq(node.getDeclarationSymbol(), "Function");

    node.type = oA::Lang::DeclarationNode::EventDeclaration;
    cr_assert_eq(node.getDeclarationSymbol(), "Event");

    node.type = static_cast<oA::Lang::DeclarationNode::DeclarationType>(4);
    cr_assert_eq(node.getDeclarationSymbol(), "");
}