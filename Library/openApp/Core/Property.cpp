/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Property
*/

#include <openApp/Core/Property.hpp>

oA::Property &oA::Property::operator=(Property &&other)
{
    swap(other);
    return *this;
}

bool oA::Property::compute(void)
{
    if (!_tree)
        return false;
    auto value = _tree->compute();
    if (Var::operator==(*value))
        return false;
    Var::operator=(*value);
    return true;
}

void oA::Property::depends(const PropertyPtr &target)
{
    _dependencies.emplace_back(std::make_pair(
        target->connect([this]{
            compute();
            return true;
        }),
        target
    ));
}

void oA::Property::call(void)
{
    if (!compute())
        this->emit();
}

oA::Uint oA::Property::connectEvent(PropertyPtr &&ptr)
{
    if (!ptr)
        throw LogicError("Property", "Can't add @null@ event");
    return this->connect([event = std::move(ptr)](void) mutable {
        event->call();
        return true;
    });
}

void oA::Property::show(Int tab) const noexcept
{
    if (_tree)
        Lang::ASTNode::ShowTree(*_tree, tab);
}

void oA::Property::setTree(Lang::ASTNodePtr &&tree)
{
    if (_tree)
        clearTree();
    if (!tree)
        throw LogicError("Property", "Can't set null expression @tree@");
    else if (tree->isConst())
        Var::operator=(*tree->compute());
    else
        _tree = std::move(tree);
}

void oA::Property::clearTree(void)
{
    _dependencies.apply([](auto &pair) { pair.second->disconnect(pair.first); });
    _dependencies.clear();
    _tree.reset();
}

void oA::Property::swap(Property &other)
{
    Var::swap(other);
    _tree.swap(other._tree);
}