/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ASTNode
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <openApp/Language/Nodes.hpp>

Test(ASTNode, Basics)
{
    oA::Lang::ASTNode node;
    oA::Lang::ASTNode::ReturnSignal sig(oA::Var(42));
    bool crashed = false;

    cr_assert_eq(sig.value.toInt(), 42);
    try { node.compute(); }
    catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
}

Test(ASTNode, Show, .init=cr_redirect_stdout)
{
    oA::Var var = 1;
    oA::Lang::ASTNode tree;

    tree.emplaceAs<oA::Lang::ImportNode>("path");
    tree.emplaceAs<oA::Lang::ClassNode>("Name", "ID");
    tree.emplaceAs<oA::Lang::DeclarationNode>("name", oA::Lang::DeclarationNode::AssignmentDeclaration).tokens.emplace_back(std::make_pair("token", 1));
    tree.emplaceAs<oA::Lang::GroupNode>();
    tree.emplaceAs<oA::Lang::ExpressionGroupNode>();
    tree.emplaceAs<oA::Lang::ReferenceNode>(std::make_unique<oA::Expression>());
    tree.emplaceAs<oA::Lang::LocalNode>(var);
    tree.emplaceAs<oA::Lang::ValueNode>();
    tree.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Division);
    tree.emplaceAs<oA::Lang::StatementNode>(oA::Lang::If);
    oA::Lang::ASTNode::ShowTree(tree);
}