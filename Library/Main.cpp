/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openApp/Language/Nodes.hpp>

void cr_assert(bool res)
{
    if (!res)
        throw;
}

template<typename T>
void cr_assert_eq(const T &x, const T &y)
{
    if (x != y)
        throw;
}

int main(void)
{
    oA::Lang::ExpressionGroupNode root;
    auto expr(std::make_shared<oA::Expression>(0));
    auto &node = root.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement);

    root.locals["var"] = oA::Container();
    root.locals["var"] += 42;
    auto &at = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::At);
    at.emplaceAs<oA::Lang::LocalNode>(root.locals["var"]);
    at.emplaceAs<oA::Lang::ValueNode>().value = 0;

    cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::SufixDecrement;         cr_assert_eq(node.compute().toInt(), 1);
    node.op = oA::Lang::PrefixDecrement;        cr_assert_eq(node.compute().toInt(), -1);
    node.op = oA::Lang::SufixIncrement;         cr_assert_eq(node.compute().toInt(), -1);

    node.emplaceAs<oA::Lang::ValueNode>().value = oA::Container();
    node.op = oA::Lang::Assign;
    cr_assert_eq(node.compute().toInt(), 2);
}