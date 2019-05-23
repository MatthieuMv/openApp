/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

// Vector
#include "Core/Vector.hpp"
// Pair
#include "Core/Pair.hpp"
// Operator
#include "Core/ExpressionStack.hpp"
// Log
#include "Core/Log.hpp"

namespace oA
{
    template<typename T>
    class Expression;
}

/*
    An Expression is a Property which depends on other properties
    If a dependency changes, the whole expression is re-computed
    It can also hold events, which are other expression called on emit(),
    these can be interpreted as runtime events functions.
*/
template<typename T>
class oA::Expression : public Property<T>
{
public:
    using Property<T>::Property;
    using Node = ExpressionNode<T>;

    virtual ~Expression(void) {}

    void addNode(OperatorType op) {
        _expr.emplace_back(MakePair(0, Node(op)));
    }

    void addNode(const T &value) {
        _expr.emplace_back(MakePair(0, Node(value)));
    }

    void addNode(const ExpressionPtr<T> &property, bool hasDependencies = true) {
        Uint idx = 0;
        if (hasDependencies && property.get() != this)
            idx = depends(*property);
        _expr.emplace_back(MakePair(idx, Node(property)));
    }

    void clear(void) {
        for (auto &pair : _expr) {
            if (pair.first && pair.second.isExpression())
                pair.second.getExpression()->disconnect(pair.first);
        }
        _expr.clear();
    }

    template<typename U>
    Uint depends(Property<U> &other) noexcept {
        return other.connect([this] {
            this->compute();
            return true;
        });
    }

    void compute(void) {
        ExpressionStack<T> stack;
        if (_expr.empty())
            return;
        for (auto &pair : _expr) {
            if (pair.second.isOperator())
                stack.processOperator(pair.second.getOperator());
            else
                stack.push(pair.second);
        }
        if (stack.size() != 1)
            throw LogicError("Expression", "Non-null expression must have only @1 return value@");
        Property<T>::set(stack.top().getValue());
    }

    Expression<T> &addEvent(void) {
        _events.emplace_back(MakeShared<Expression<T>>());
        return (*_events.back());
    }

    void popEvent(void) {
        _events.pop_back();
    }

    void clearEvents(void) {
        _events.clear();
    }

    void show(void) const {
        auto i = 0;
        cout << "#Expression#: ";
        for (const auto &p : _expr) {
            if (i)
                cout << " ";
            ++i;
            if (p.second.op)
                cout << '@' + GetOperatorString(p.second.op) + '@';
            else
                cout << p.second.property->get();
        }
        cout << endl;
    }

    virtual void emit(void) override {
        Property<T>::emit();
        for (auto &event : _events) {
            event->compute();
        }
    }

private:
    Vector<Pair<Uint, Node>> _expr;
    Vector<ExpressionPtr<T>> _events;
};