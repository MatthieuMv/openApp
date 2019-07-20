/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include <openApp/Core/Log.hpp>
#include <openApp/App/Item.hpp>

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

void oA::Item::setExpression(Expression &target, String expression, bool addDependency)
{
    (void)(target);
    (void)(expression);
    (void)(addDependency);
}

oA::Item *oA::Item::findItem(const String &key, FindWhere where)
{
    Item *ptr = nullptr;

    if (key == getID())
        return this;
    if (childExists(key))
        return &getChild(key);
    if ((where == Parents || where == Everywhere) && (ptr = findParents(key)))
        return ptr;
    if (where == Children || where == Everywhere)
        ptr = findChildren(key);
    return ptr;
}

oA::Item *oA::Item::findParents(const String &key)
{
    if (!_parent)
        return nullptr;
    if (key == "parent" || key == _parent->getID())
        return _parent;
    if (_parent->childExists(key))
        return &_parent->getChild(key);
    for (auto &child : _parent->_children) {
        if (child.get() == this)
            continue;
        auto ptr = child->findItem(key, Children);
        if (ptr)
            return ptr;
    }
    return _parent->findParents(key);
}

oA::Item *oA::Item::findChildren(const String &key)
{
    for (auto &child : _children) {
        if (child->childExists(key))
            return &child->getChild(key);
    }
    for (auto &child : _children) {
        auto ptr = child->findChildren(key);
        if (ptr)
            return ptr;
    }
    return nullptr;
}

oA::ExpressionPtr oA::Item::findExpr(const String &key)
{
    ExpressionPtr res;
    String token, left = SplitKeyExpr(key, token);

    if (!token.empty() && token == getID())
        return findExpr(left);
    if (left.empty())
        return getExprPtr(key);
    auto ptr = findItem(token);
    if (ptr)
        return ptr->findExpr(left);
    return ExpressionPtr();
}

void oA::Item::show(Int tab) const noexcept
{
    cout << Repeat(tab) << '\t' << '@' << getName() << "@:" << endl;
    ++tab;
    _members.apply([tab](const auto &p) mutable {
        cout << Repeat(tab) << '\t' << '@' << p.first << "@:" << endl;
        p.second->show(tab + 1);
    });
    _children.apply([tab](const auto &child) { child->show(tab); });

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