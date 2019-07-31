/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_OperatorNode
*/

#include <criterion/criterion.h>
#include <openApp/Core/Expression.hpp>
#include <openApp/Language/Nodes.hpp>

Test(OperatorNode, Basics)
{
    oA::Lang::OperatorNode node(oA::Lang::Not);
    bool crashed = false;

    node.emplaceAs<oA::Lang::ValueNode>().value = 1;

    cr_assert_eq(node.compute().toBool(), false);

    try { node.op = oA::Lang::PrefixIncrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::PrefixDecrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::SufixIncrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::SufixDecrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::Call; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;

    node.emplaceAs<oA::Lang::ValueNode>().value = 2;

    node.op = oA::Lang::Equal;                  cr_assert_eq(node.compute().toBool(), false);
    node.op = oA::Lang::Different;              cr_assert_eq(node.compute().toBool(), true);
    node.op = oA::Lang::Superior;               cr_assert_eq(node.compute().toBool(), false);
    node.op = oA::Lang::SuperiorEqual;          cr_assert_eq(node.compute().toBool(), false);
    node.op = oA::Lang::Inferior;               cr_assert_eq(node.compute().toBool(), true);
    node.op = oA::Lang::InferiorEqual;          cr_assert_eq(node.compute().toBool(), true);
    node.op = oA::Lang::Addition;               cr_assert_eq(node.compute().toInt(), 3);
    node.op = oA::Lang::Substraction;           cr_assert_eq(node.compute().toInt(), -1);
    node.op = oA::Lang::Multiplication;         cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::Division;               cr_assert_eq(node.compute().toInt(), 0);
    node.op = oA::Lang::Modulo;                 cr_assert_eq(node.compute().toInt(), 1);

    try { node.op = oA::Lang::Assign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::AdditionAssign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::SubstractionAssign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::MultiplicationAssign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::DivisionAssign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::ModuloAssign; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::TernaryElse; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::Comma; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::End; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::LeftParenthese; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::RightParenthese; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::LeftBracket; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::RightBracket; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::LeftBrace; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::RightBrace; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::At; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;

    node.emplaceAs<oA::Lang::ValueNode>().value = 3;

    node.op = oA::Lang::TernaryIf;              cr_assert_eq(node.compute().toInt(), 2);
}

Test(OperatorNode, Assignment)
{
    auto expr(std::make_shared<oA::Expression>(0));
    oA::Lang::OperatorNode node(oA::Lang::PrefixIncrement);

    node.emplaceAs<oA::Lang::ReferenceNode>(std::move(expr));

    cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::SufixDecrement;         cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::PrefixDecrement;        cr_assert_eq(node.compute().toInt(), -1);
    node.op = oA::Lang::SufixIncrement;         cr_assert_eq(node.compute().toInt(), -1);

    node.emplaceAs<oA::Lang::ValueNode>().value = 2;
    node.op = oA::Lang::Assign;                 cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::AdditionAssign;         cr_assert_eq(node.compute().toInt(), 4);
    node.op = oA::Lang::SubstractionAssign;     cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::MultiplicationAssign;   cr_assert_eq(node.compute().toInt(), 4);
    node.op = oA::Lang::DivisionAssign;         cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::ModuloAssign;           cr_assert_eq(node.compute().toInt(), 0);
}

Test(OperatorNode, LocalAssignment)
{
    oA::Lang::ExpressionGroupNode root;
    auto expr(std::make_shared<oA::Expression>(0));
    auto &node = root.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement);

    root.locals["var"] = 0;
    node.emplaceAs<oA::Lang::LocalNode>(root.locals["var"]);

    cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::SufixDecrement;         cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::PrefixDecrement;        cr_assert_eq(node.compute().toInt(), -1);
    node.op = oA::Lang::SufixIncrement;         cr_assert_eq(node.compute().toInt(), -1);

    node.emplaceAs<oA::Lang::ValueNode>().value = 2;
    node.op = oA::Lang::Assign;                 cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::AdditionAssign;         cr_assert_eq(node.compute().toInt(), 4);
    node.op = oA::Lang::SubstractionAssign;     cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::MultiplicationAssign;   cr_assert_eq(node.compute().toInt(), 4);
    node.op = oA::Lang::DivisionAssign;         cr_assert_eq(node.compute().toInt(), 2);
    node.op = oA::Lang::ModuloAssign;           cr_assert_eq(node.compute().toInt(), 0);
}

Test(OperatorNode, ContainerAssignment)
{
    oA::Lang::ExpressionGroupNode root;
    auto expr(std::make_shared<oA::Expression>(0));
    auto &node = root.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement);

    root.locals["var"] = oA::Container();
    root.locals["var"] += 0;
    auto &at = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::At);
    at.emplaceAs<oA::Lang::LocalNode>(root.locals["var"]);
    at.emplaceAs<oA::Lang::ValueNode>().value = 0;
    cr_assert_eq(node.compute().toInt(), 1);

    node.op = oA::Lang::SufixDecrement;         cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::PrefixDecrement;        cr_assert_eq(node.compute().toInt(), -1);
    node.op = oA::Lang::SufixIncrement;         cr_assert_eq(node.compute().toInt(), -1);

    node.emplaceAs<oA::Lang::ValueNode>().value = oA::Container();
    node.op = oA::Lang::Assign;                 cr_assert_eq(node.compute(), oA::Container());
}