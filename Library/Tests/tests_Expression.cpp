/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Expression
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <openApp/Core/Expression.hpp>
#include <openApp/Language/Nodes.hpp>

Test(Expression, Basics)
{
    oA::ExpressionPtr ptr(std::make_shared<oA::Expression>(23));
    oA::Expression main(42), toMove(main), other(std::move(toMove)), event;

    oA::Lang::ASTNodePtr tree(std::make_unique<oA::Lang::ExpressionGroupNode>());
    auto &op = tree->emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Operator::PrefixIncrement);
    op.emplaceAs<oA::Lang::ReferenceNode>(oA::ExpressionPtr(ptr));
    event.setTree(std::move(tree));

    main = 1;
    cr_assert_eq(main->toInt(), 1);
    cr_assert_eq(other->toInt(), 42);
    cr_assert_eq((*ptr)->toInt(), 23);
    main.depends(other);

    main.connectEvent(std::move(event));
    main.call();
    cr_assert_eq(main->toInt(), 1);
    cr_assert_eq(other->toInt(), 42);
    cr_assert_eq((*ptr)->toInt(), 24);
    
    other = 4;
    cr_assert_eq(main->toInt(), 1);
    cr_assert_eq(other->toInt(), 4);
    cr_assert_eq((*ptr)->toInt(), 24);

    main.swap(other);
    cr_assert_eq(main->toInt(), 4);
    cr_assert_eq(other->toInt(), 1);
    cr_assert_eq((*ptr)->toInt(), 24);
}

Test(Expression, Show, .init=cr_redirect_stdout)
{
    oA::Expression event;
    oA::Lang::ASTNodePtr tree(std::make_unique<oA::Lang::ExpressionGroupNode>());

    tree->emplaceAs<oA::Lang::ValueNode>();
    event.show();
    event.setTree(std::move(tree));
    event.show();
}