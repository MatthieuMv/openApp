/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ShuntingYard
*/

#include <criterion/criterion.h>
#include <openApp/Language/ShuntingYard.hpp>

Test(ShuntingYard, BasicExpression)
{
    oA::Item item;

    item.get("y") = 1;
    oA::Lang::ShuntingYard::ProcessString(item, "x", "y * 2", oA::Lang::ShuntingYard::Expression);
    cr_assert_eq(item.getAs<oA::Number>("x"), 2);
    item.get("y") = 2;
    cr_assert_eq(item.getAs<oA::Number>("x"), 4);
}

Test(ShuntingYard, BasicFunction)
{
    oA::Item item;

    item.append("function");
    oA::Lang::ShuntingYard::ProcessString(item, "function", "x = 42", oA::Lang::ShuntingYard::Function);
    item.getPtr("function")->call();
    cr_assert_eq(item.getAs<oA::Number>("x"), 42);
}

Test(ShuntingYard, BasicEvent)
{
    oA::Item item;

    oA::Lang::ShuntingYard::ProcessString(item, "x", "y = 42", oA::Lang::ShuntingYard::Event);
    cr_assert_eq(item.getAs<oA::Number>("y"), 0);
    ++item.get("x");
    cr_assert_eq(item.getAs<oA::Number>("y"), 42);
}

Test(ShuntingYard, MediumExpression)
{
    oA::Item item;

    item.get("y") = 1;
    oA::Lang::ShuntingYard::ProcessString(item, "x", "(((y >= 2 ? 42 : 24) * 2) / 4) * 2", oA::Lang::ShuntingYard::Expression);
    cr_assert_eq(item.getAs<oA::Number>("x"), 24);
    item.get("y") = 2;
    cr_assert_eq(item.getAs<oA::Number>("x"), 42);
}

Test(ShuntingYard, MediumFunction)
{
    oA::Item item;

    item.append("function");
    oA::Lang::ShuntingYard::ProcessString(item, "function", "if (y) { x = 4 } else { x = 3 }", oA::Lang::ShuntingYard::Function);
    item.getPtr("function")->call();
    cr_assert_eq(item.getAs<oA::Number>("x"), 3);
    item.get("y") = 1;
    item.getPtr("function")->call();
    cr_assert_eq(item.getAs<oA::Number>("x"), 4);
}

Test(ShuntingYard, MediumEvent)
{
    oA::Item item;

    oA::Lang::ShuntingYard::ProcessString(item, "x",
"switch (x) {\n\
case 1:\n\
    y = 4;\n\
    break;\n\
case 2:\n\
    y = 42;\n\
    break;\n\
case 3:\n\
    y = 420;\n\
    break;\n\
default:\n\
    y = 10;\n\
    break;\n\
}", oA::Lang::ShuntingYard::Event);
    ++item.get("x");
    cr_assert_eq(item.getAs<oA::Number>("y"), 4);
    ++item.get("x");
    cr_assert_eq(item.getAs<oA::Number>("y"), 42);
    ++item.get("x");
    cr_assert_eq(item.getAs<oA::Number>("y"), 420);
    ++item.get("x");
    cr_assert_eq(item.getAs<oA::Number>("y"), 10);
}

// Test(ShuntingYard, AdvancedExpression)
// {
//     oA::Item item;

//     item.get("y") = 1;
//     oA::Lang::ShuntingYard::ProcessString(item, "x", "", oA::Lang::ShuntingYard::Expression);
//     cr_assert_eq(item.getAs<oA::Number>("x"), 2);
// }

// Test(ShuntingYard, AdvancedFunction)
// {
//     oA::Item item;

//     item.append("function");
//     oA::Lang::ShuntingYard::ProcessString(item, "function", "", oA::Lang::ShuntingYard::Function);
//     item.getPtr("function")->call();
//     cr_assert_eq(item.getAs<oA::Number>("x"), 42);
// }

// Test(ShuntingYard, AdvancedEvent)
// {
//     oA::Item item;

//     oA::Lang::ShuntingYard::ProcessString(item, "x", "", oA::Lang::ShuntingYard::Event);
//     cr_assert_eq(item.getAs<oA::Number>("y"), 0);
//     ++item.get("x");
//     cr_assert_eq(item.getAs<oA::Number>("y"), 42);
// }