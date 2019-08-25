/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_StatementNode
*/

#include <criterion/criterion.h>
#include <openApp/Language/Nodes.hpp>

Test(StatementNode, If)
{
    oA::Lang::StatementNode node(oA::Lang::If);
    auto &condition = node.emplaceAs<oA::Lang::ValueNode>(0);

    node.emplaceAs<oA::Lang::ValueNode>(1);
    cr_assert_eq(node.compute()->toInt(), 0);
    condition.value = 1;
    node.emplaceAs<oA::Lang::ValueNode>(2);
    cr_assert_eq(node.compute()->toInt(), 1);
    condition.value = 0;
    cr_assert_eq(node.compute()->toInt(), 2);
}

Test(StatementNode, Else)
{
    oA::Lang::StatementNode node(oA::Lang::Else);
    bool crashed = false;

    try { node.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(StatementNode, Switch)
{
    oA::Var var;
    oA::Lang::StatementNode node(oA::Lang::Switch);
    auto &comp = node.emplaceAs<oA::Lang::ValueNode>(24);

    cr_assert_eq(node.compute()->toInt(), 0);

    auto &caseNode = node.emplaceAs<oA::Lang::GroupNode>(); // Case node

    caseNode.emplaceAs<oA::Lang::ValueNode>(24);
    auto &c1 = caseNode.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Assign);
    c1.emplaceAs<oA::Lang::LocalNode>(var);
    c1.emplaceAs<oA::Lang::ValueNode>(1);

    caseNode.emplaceAs<oA::Lang::ValueNode>(42);
    auto &c2 = caseNode.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Assign);
    c2.emplaceAs<oA::Lang::LocalNode>(var);
    c2.emplaceAs<oA::Lang::ValueNode>(2);

    auto &def = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Assign);
    def.emplaceAs<oA::Lang::LocalNode>(var);
    def.emplaceAs<oA::Lang::ValueNode>(3);

    node.compute(); cr_assert_eq(var.toInt(), 1);
    comp.value = 42;
    node.compute(); cr_assert_eq(var.toInt(), 2);
    comp.value = 0;
    node.compute(); cr_assert_eq(var.toInt(), 3);
}

Test(StatementNode, Case)
{
    oA::Lang::StatementNode node(oA::Lang::Case);
    bool crashed = false;

    try { node.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(StatementNode, Default)
{
    oA::Lang::StatementNode node(oA::Lang::Default);
    bool crashed = false;

    try { node.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(StatementNode, While)
{
    oA::Var var = 0;
    oA::Lang::StatementNode node(oA::Lang::While);

    auto &cond = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Inferior);
    cond.emplaceAs<oA::Lang::LocalNode>(var);
    cond.emplaceAs<oA::Lang::ValueNode>(3);

    node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement).emplaceAs<oA::Lang::LocalNode>(var);

    node.compute();
    cr_assert_eq(var.toInt(), 3);
}

Test(StatementNode, For)
{
    oA::Var v1, v2, v3;
    oA::Lang::StatementNode node(oA::Lang::For);

    auto &init = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Assign);
    init.emplaceAs<oA::Lang::LocalNode>(v1);
    init.emplaceAs<oA::Lang::ValueNode>(42);
    auto &cond = node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::Inferior);
    cond.emplaceAs<oA::Lang::LocalNode>(v2);
    cond.emplaceAs<oA::Lang::ValueNode>(3);
    node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement).emplaceAs<oA::Lang::LocalNode>(v2);
    node.emplaceAs<oA::Lang::OperatorNode>(oA::Lang::PrefixIncrement).emplaceAs<oA::Lang::LocalNode>(v3);
    node.compute();
    cr_assert_eq(v1.toInt(), 42);
    cr_assert_eq(v2.toInt(), 3);
    cr_assert_eq(v3.toInt(), 3);
}

Test(StatementNode, Break)
{
    oA::Lang::StatementNode node(oA::Lang::Break);
    bool crashed = true;

    try { node.compute(); }
    catch (const oA::Lang::ASTNode::BreakSignal &) { crashed = false; }
    catch (...) {}
    cr_assert_not(crashed);
}

Test(StatementNode, Return)
{
    oA::Lang::StatementNode node(oA::Lang::Return);
    bool crashed = true;

    node.emplaceAs<oA::Lang::ValueNode>(42);
    try { node.compute(); }
    catch (const oA::Lang::ASTNode::ReturnSignal &ret) { crashed = false; cr_assert_eq(ret.value->toInt(), 42); }
    catch (...) {}
    cr_assert_not(crashed);
}

Test(StatementNode, Variable)
{
    oA::Lang::StatementNode node(oA::Lang::Variable);
    bool crashed = false;

    try { node.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(StatementNode, StaticVariable)
{
    oA::Lang::StatementNode node(oA::Lang::StaticVariable);
    bool crashed = false;

    try { node.compute(); } catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(StatementNode, WhileSignals)
{
    oA::Lang::StatementNode node(oA::Lang::While);
    oA::Var value;

    node.emplaceAs<oA::Lang::ValueNode>(1);
    auto &sig = node.emplaceAs<oA::Lang::StatementNode>(oA::Lang::Break);
    node.compute();
    sig.statement = oA::Lang::Return;
    sig.emplaceAs<oA::Lang::ValueNode>(42);
    try { node.compute(); }
    catch (const oA::Lang::ASTNode::ReturnSignal &ret) { value = *ret.value; }
    cr_assert_eq(value.toInt(), 42);
}

Test(StatementNode, ForSignals)
{
    oA::Lang::StatementNode node(oA::Lang::For);
    oA::Var value;

    node.emplaceAs<oA::Lang::ValueNode>(1);
    node.emplaceAs<oA::Lang::ValueNode>(1);
    node.emplaceAs<oA::Lang::ValueNode>(1);
    auto &sig = node.emplaceAs<oA::Lang::StatementNode>(oA::Lang::Break);
    node.compute();
    sig.statement = oA::Lang::Return;
    sig.emplaceAs<oA::Lang::ValueNode>(42);
    try { node.compute(); }
    catch (const oA::Lang::ASTNode::ReturnSignal &ret) { value = *ret.value; }
    cr_assert_eq(value.toInt(), 42);
}

Test(StatementNode, SwitchSignals)
{
    oA::Lang::StatementNode node(oA::Lang::Switch);
    oA::Var value;

    node.emplaceAs<oA::Lang::ValueNode>(1);
    node.emplaceAs<oA::Lang::ValueNode>(1);
    auto &sig = node.emplaceAs<oA::Lang::StatementNode>(oA::Lang::Break);
    node.compute();
    sig.statement = oA::Lang::Return;
    sig.emplaceAs<oA::Lang::ValueNode>(42);
    try { node.compute(); }
    catch (const oA::Lang::ASTNode::ReturnSignal &ret) { value = *ret.value; }
    cr_assert_eq(value.toInt(), 42);
}