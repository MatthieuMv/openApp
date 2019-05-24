/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

// Item
#include "App/Item.hpp"
// IStringStream
#include "Core/StringStream.hpp"

static void PopUntil(oA::Expression<oA::Var> &target, oA::Item::OperatorStack &stack, oA::OperatorType type);
static void CheckOp(oA::Expression<oA::Var> &target, oA::Item::OperatorStack &stack, const oA::Operator &op);
static oA::String &FormatString(oA::String &str);

oA::Expression<oA::Var> &oA::Item::getExpr(const String &name)
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find expression @" + name + "@");
    return (*it->second);
}

const oA::Expression<oA::Var> &oA::Item::getExpr(const String &name) const
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        throw AccessError("Item", "Couldn't find expression @" + name + "@");
    return (*it->second);
}

oA::ExpressionPtr<oA::Var> oA::Item::getExprPtr(const String &name)
{
    auto it = _properties.find(name);

    if (it == _properties.end())
        return ExpressionPtr<Var>();
    return (it->second);
}

void oA::Item::makeExpression(const String &name, const String &targetExpr)
{
    auto &target = getExpr(name);

    try {
        target.clear();
        makeExpression(target, targetExpr, true, true);
    } catch (const Error &e) {
        target.clear();
        throw RuntimeError("Item", "Expression @" + name + "@: " + targetExpr + "\n\t-> " + e.what());
    }
}

void oA::Item::makeExpression(Expression<Var> &target, const String &targetExpr, bool hasDependencies, bool compute)
{
    auto expr = targetExpr, tmp = String();

    FormatExpression(expr);
    IStringStream ss(expr);
    OperatorStack stack;

    while (ss >> expr) {
        if (expr.front() == '"' && expr.back() != '"') {
            std::getline(ss, tmp, '"');
            expr += tmp;
            expr.push_back('"');
        }
        if (OperatorExists(expr))
            insertOperator(target, stack, expr);
        else
            insertOperand(target, expr, hasDependencies);
    }
    PopUntil(target, stack, None);
    if (compute)
        target.compute();
}

void oA::Item::insertOperator(Expression<Var> &target, OperatorStack &stack, const String &str)
{
    const auto op = GetOperator(str);
    switch (op.type) {
    case LeftParenthesis: // left parenthesis
        return stack.push(op);
    case RightParenthesis: // right parenthesis
        return PopUntil(target, stack, LeftParenthesis);
    case Else:
        return;
    default:
        return CheckOp(target, stack, op);
    }
}

static void PopUntil(oA::Expression<oA::Var> &target, oA::Item::OperatorStack &stack, oA::OperatorType type)
{
    if (stack.empty() && type == oA::None)
        return;
    while (!stack.empty()) {
        auto &op = stack.top();
        if (op.type == type) {
            stack.pop();
            return;
        }
        target.addNode(op.type);
        stack.pop();
    }
    if (type != oA::None)
        throw oA::LogicError("Item", "Couldn't find left parenthesis");
}

static void CheckOp(oA::Expression<oA::Var> &target, oA::Item::OperatorStack &stack, const oA::Operator &op)
{
    oA::UByte p1 = 0, p2 = 0;

    if (stack.empty() || stack.top().type == oA::LeftParenthesis)
        return stack.push(op);
    p1 = op.priority;
    p2 = stack.top().priority;
    if (p1 < p2 || (p1 == p2 && op.flow == oA::LeftToRight))
        return stack.push(op);
    while (p1 > p2 || (p1 == p2 && op.flow == oA::RightToLeft)) {
        target.addNode(stack.top().type);
        stack.pop();
        if (stack.empty())
            break;
        p2 = stack.top().priority;
    }
    stack.push(op);
}

void oA::Item::insertOperand(Expression<Var> &target, String &operand, bool hasDependencies)
{
    if (IsString(operand))
        return target.addNode(FormatString(operand));
    else if (IsNumber(operand))
        return target.addNode(std::stof(operand));
    else if (IsBoolean(operand))
        return target.addNode(FromBoolean(operand));
    auto p = findExpression(operand);
    if (!p)
        throw AccessError("Item", "Couldn't insert operand @" + operand + "@");
    target.addNode(p, hasDependencies);
}

static oA::String &FormatString(oA::String &str)
{
    str.erase(str.begin());
    str.pop_back();
    return (str);
}

void oA::Item::addExpressionEvent(const oA::String &name, const oA::String &targetExpr)
{
    auto p = getExprPtr(name);

    if (!p)
        throw AccessError("Item", "Expression @" + name + "@ doesn't exists");
    auto &evt = p->addEvent();
    try {
        makeExpression(evt, targetExpr, false, false);
    } catch (const Error &e) {
        p->popEvent();
        throw RuntimeError("Item", "Expression event @" + name + "@: " + targetExpr + "\n\t-> " + e.what());
    }
}