/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemFind
*/

// Item
#include "App/Item.hpp"

static oA::String SplitExpression(const oA::String &expr, oA::String &token);

oA::Item *oA::Item::find(const String &name)
{
    Item *ptr = nullptr;

    if (childExists(name))
        return getChildPtr(name).get();
    ptr = findInParents(name);
    if (ptr)
        return ptr;
    ptr = findInChildrens(name);
    return ptr;
}

oA::Item *oA::Item::findInParents(const String &name)
{
    if (!_parent)
        return nullptr;
    if (name == "parent" || name == _parent->get("id")->get<String>())
        return _parent;
    if (_parent->childExists(name))
        return _parent->getChildPtr(name).get();
    return _parent->findInParents(name);
}

oA::Item *oA::Item::findInChildrens(const String &name)
{
    Item *ptr = nullptr;

    for (auto &child : _childs) {
        if (child->childExists(name))
            return child->getChildPtr(name).get();
    }
    for (auto &child : _childs) {
        ptr = child->findInChildrens(name);
        if (ptr)
            return ptr;
    }
    return nullptr;
}

oA::PropertyPtr<oA::Var> oA::Item::findProperty(const String &name)
{
    PropertyPtr<Var> res;
    String token, left = SplitExpression(name, token);

    if (!token.empty() && token == get("id")->getConst<String>())
        return findProperty(left);
    if (left.empty())
        return getPtr(name);
    auto ptr = find(token);
    if (ptr)
        return ptr->findProperty(left);
    return PropertyPtr<Var>();
}

static oA::String SplitExpression(const oA::String &expr, oA::String &token)
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