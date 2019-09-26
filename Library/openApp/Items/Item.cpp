/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Item
*/

#include <openApp/Core/Log.hpp>
#include <openApp/Items/Item.hpp>
#include <openApp/Language/ShuntingYard.hpp>

static oA::String SplitKeyExpr(const oA::String &expr, oA::String &token);

void oA::Item::onAppendChild(Item &child)
{
    static auto assigned = 0;

    if (child.getID().empty()) {
        child.setID("noID" + ToString(assigned++));
    }
    child.setParent(this);
    setChildScreenPos(child);
}

void oA::Item::setChildScreenPos(Item &child)
{
    child.setExpression("screenX", "x + parent.screenX");
    child.setExpression("screenY", "y + parent.screenY");
}

void oA::Item::onRemoveChild(Item &child)
{
    child.setParent(nullptr);
}

void oA::Item::onParentChanged(void)
{
    if (getParent())
        return;
    (get("screenX") = 0).clearTree();
    (get("screenY") = 0).clearTree();
}


void oA::Item::update(IRenderer &renderer)
{
    if (!get("enabled"))
        return;
    onUpdate(renderer);
    _children.apply([&renderer](auto &child) {
        child->update(renderer);
    });
}

void oA::Item::draw(IRenderer &renderer, const AreaContext &clipArea)
{
    auto processDraw = [this](IRenderer &renderer, const AreaContext &area) {
        onDraw(renderer);
        for (auto &child : _children) {
            child->draw(renderer, area);
        }
    };

    if (!get("visible"))
        return;
    if (!get("clip")) {
        processDraw(renderer, clipArea);
        return;
    }
    auto area = getClipArea(clipArea);
    if (area.size.x <= 0 || area.size.y <= 0)
        return;
    renderer.setClippingArea(area);
    processDraw(renderer, area);
    renderer.setClippingArea(clipArea);
}

oA::AreaContext oA::Item::getClipArea(const AreaContext &parent)
{
    auto area = getAreaContext();

    if (area.pos.x < parent.pos.x) {
        area.size.x -= parent.pos.x - area.pos.x;
        area.pos.x = parent.pos.x;
    }
    if (area.pos.y < parent.pos.y) {
        area.size.y -= parent.pos.y - area.pos.y;
        area.pos.y = parent.pos.y;
    }
    if (area.pos.x + area.size.x > parent.pos.x + parent.size.x)
        area.size.x -= area.pos.x + area.size.x - (parent.pos.x + parent.size.x);
    if (area.pos.y + area.size.y > parent.pos.y + parent.size.y)
        area.size.y -= area.pos.y + area.size.y - (parent.pos.y + parent.size.y);
    return area;
}

bool oA::Item::propagate(IRenderer &renderer, const Event &event)
{
    if (!get("enabled"))
        return false;
    for (auto it = _children.rbegin(); it != _children.rend(); ++it) {
        if ((*it)->propagate(renderer, event))
            return true;
    }
    if (onEvent(renderer, event))
        return true;
    return false;
}

void oA::Item::setExpression(const String &key, const String &expression, const String &context)
{
    if (!exists(key))
        append(key);
    Lang::ShuntingYard::ProcessString(*this, key, expression, Lang::ShuntingYard::Expression, context ? context : key);
}

void oA::Item::setFunction(const String &key, const String &expression, const String &context)
{
    if (!exists(key))
        append(key);
    Lang::ShuntingYard::ProcessString(*this, key, expression, Lang::ShuntingYard::Function, context ? context : key);
}

void oA::Item::addExpressionEvent(const String &key, const String &expression, const String &context)
{
    Lang::ShuntingYard::ProcessString(*this, key, expression, Lang::ShuntingYard::Event, context ? context : key);
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

oA::PropertyPtr oA::Item::findExpr(const String &key)
{
    PropertyPtr res;
    String token, left = SplitKeyExpr(key, token);

    if (!token.empty() && token == getID())
        return findExpr(left);
    if (left.empty())
        return getPtr(key);
    auto ptr = findItem(token);
    if (ptr)
        return ptr->findExpr(left);
    return PropertyPtr();
}

void oA::Item::show(Int tab) const noexcept
{
    cout << Repeat(tab++) << "   " << '#' << getName() << "# " << getID() << " {" << endl;
    _members.apply([tab](const auto &p) mutable {
        cout << Repeat(tab) << "   " << '@' << p.first << "@: " << p.second->toString() << endl;
        p.second->show(tab + 1);
    });
    _children.apply([tab](const auto &child) { child->show(tab); });
    cout << Repeat(--tab) << "   " << "}" << endl;

}

static oA::String SplitKeyExpr(const oA::String &expr, oA::String &token)
{
    auto it = expr.find('.');
    oA::String left;

    if (it == expr.npos) {
        token = expr;
        return left;
    }
    if (it) {
        token = expr.substr(0, it);
        left = expr.substr(it + 1);
    }
    if (left.empty())
        throw oA::LogicError("Item", "Invalid expression @" + expr + "@");
    return left;
}