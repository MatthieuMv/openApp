/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#include <openApp/App/ExpressionHandler.hpp>

oA::Property<oA::Var> &oA::ItemUtils::ExpressionHandler::append(const String &key)
{
    if (exists(key))
        throw LogicError("Item", "Can't append @" + key + "@, already exists");
    return *(_members[key] = std::make_shared<Expression>());
}

bool oA::ItemUtils::ExpressionHandler::exists(const String &key) const noexcept
{
    return _members.find(key) != _members.end();
}

oA::Property<oA::Var> &oA::ItemUtils::ExpressionHandler::get(const String &key)
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

const oA::Property<oA::Var> &oA::ItemUtils::ExpressionHandler::get(const String &key) const
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

oA::ExpressionPtr oA::ItemUtils::ExpressionHandler::getExprPtr(const String &key) const noexcept
{
    auto it = _members.find(key);

    if (it == _members.end())
        return oA::ExpressionPtr();
    return it->second;
}