/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** PropertyHandler
*/

#include <openApp/App/PropertyHandler.hpp>

oA::Property &oA::ItemUtils::PropertyHandler::append(const String &key)
{
    if (exists(key))
        throw LogicError("Item", "Can't append @" + key + "@, already exists");
    return *(_members[key] = std::make_shared<Property>());
}

bool oA::ItemUtils::PropertyHandler::exists(const String &key) const noexcept
{
    return _members.find(key) != _members.end();
}

oA::Property &oA::ItemUtils::PropertyHandler::get(const String &key)
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

const oA::Property &oA::ItemUtils::PropertyHandler::get(const String &key) const
{
    auto it = _members.find(key);

    if (it == _members.end())
        throw AccessError("Item", "Member @" + key + "@ doesn't exists");
    return *it->second;
}

oA::PropertyPtr oA::ItemUtils::PropertyHandler::getPtr(const String &key) const noexcept
{
    auto it = _members.find(key);

    if (it == _members.end())
        return PropertyPtr();
    return it->second;
}