/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes.hpp>

void cr_assert(bool res)
{
    if (!res)
        throw;
}

template<typename T, typename U>
void cr_assert_eq(const T &x, const U &y)
{
    if (x != y)
        throw;
}

int main(void)
{
    oA::Lang::OperatorNode node(oA::Lang::Not);
    bool crashed = false;
    oA::Var var;

    node.emplaceAs<oA::Lang::ValueNode>(1);

    cr_assert_eq(node.compute().toBool(), false);

    try { node.op = oA::Lang::PrefixIncrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::PrefixDecrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::SufixIncrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::SufixDecrement; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;
    try { node.op = oA::Lang::Call; node.compute(); } catch (...) { crashed = true; } cr_assert(crashed); crashed = false;

    node.emplaceAs<oA::Lang::ValueNode>(2);
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
}