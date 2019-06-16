/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include <openApp/App/Item.hpp>

oA::Property<oA::Var> &oA::Item::append(const String &key)
{
    if (exists(key))
        throw LogicError("Item", "Can't append @" + key + "@, already exists");
    return *(_members[key] = std::make_shared<Expression<Var>>());
}

bool oA::Item::exists(const String &key) const noexcept
{
    return _members.find(key) != _members.end();
}

oA::Property<oA::Var> &oA::Item::get(const String &key)
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

const oA::Property<oA::Var> &oA::Item::get(const String &key) const
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

void oA::Item::setExpression(const String &key, const String &expression)
{
    const auto &ptr = getExprPtr(key);

    if (!ptr)
        throw AccessError("Item", "Can't set expression of @" + key + "@");
    setExpression(*ptr, expression, true);
}

void oA::Item::setFunction(const String &key, const String &expression)
{
    const auto &ptr = getExprPtr(key);

    if (!ptr)
        throw AccessError("Item", "Can't set function of @" + key + "@");
    setExpression(*ptr, expression, false);
}

void oA::Item::addExpressionEvent(const String &key, const String &expression)
{
    auto ptr = findExpr(key);

    if (!ptr)
        throw AccessError("Item", "Can't set expression event of @" + key + "@");
    setExpression(*ptr, expression, false);
}

void oA::Item::setExpression(Expression<Var> &target, String expression, bool addDependency)
{
    (void)(target);
    (void)(expression);
    (void)(addDependency);
}

oA::ExpressionPtr<oA::Var> oA::Item::getExprPtr(const String &key) const noexcept
{
    auto it = _members.find(key);

    if (it == _members.end())
        return oA::ExpressionPtr<oA::Var>();
    return it->second;
}
oA::Item *oA::Item::findItem(const String &key) const noexcept
{
    Item *ptr = nullptr;

    if (existsChild(key))
        return getItemPtr(key).get();
    ptr = findInParents(key);
    if (ptr)
        return ptr;
    ptr = findInChildren(key);
    return ptr;
}

oA::Item *oA::Item::findInParents(const String &key)
{
    if (!_parent)
        return nullptr;
    if (key == "parent" || key == _parent->get("id")->get<Literal>())
        return _parent;
    if (_parent->existsChild(key))
        return _parent->getItemPtr(key).get();
    return _parent->findInParents(key);
}

oA::Item *oA::Item::findInChildren(const String &key)
{
    Item *ptr = nullptr;

    for (auto &child : _children) {
        if (child->existsChild(key))
            return child->getItemPtr(key).get();
    }
    for (auto &child : _children) {
        ptr = child->findInChildren(key);
        if (ptr)
            return ptr;
    }
    return nullptr;
}

oA::ExpressionPtr<oA::Var> oA::Item::findExpr(const String &key) const noexcept
{
    ExpressionPtr<Var> res;
    String token, left = SplitKeyExpr(key, token);

    if (!token.empty() && token == get("id")->get<String>())
        return findExpr(left);
    if (left.empty())
        return getExprPtr(key);
    auto ptr = findItem(token);
    if (ptr)
        return ptr->findExpr(left);
    return ExpressionPtr<Var>();
}

oA::String oA::Item::SplitKeyExpr(const String &expr, String &token)
{
    auto it = expr.find('.');
    oA::String left;

    if (it == expr.npos) {
        token = expr;
        return left;
    }
    token = expr.substr(0, it);
    left = expr.substr(it + 1);
    if (left.empty())
        throw oA::LogicError("Item", "Invalid expression @" + expr + "@");
    return left;
}