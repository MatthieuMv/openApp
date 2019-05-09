/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Expression
*/

#pragma once

// Property
#include "Core/Property.hpp"
// Stack
#include "Core/Stack.hpp"
// Vector
#include "Core/Vector.hpp"
// Operator
#include "Core/Operators.hpp"
// Pair
#include "Core/Pair.hpp"

namespace oA
{
    template<typename T>
    class Expression;

    template<typename T>
    using ExpressionPtr = Shared<Expression<T>>;

    template<typename T>
    using ExpressionRef = Weak<Expression<T>>;
}

/*
    An Expression is a Property which depends on other properties
    If a dependency changes, the whole expression is re-computed
*/
template<typename T>
class oA::Expression : public Property<T>
{
    using ExpressionFct = Function<void(Stack<T> &)>;

    struct Node
    {
        Node(const Operator &holdOp) : op(holdOp) {}
        Node(const PropertyPtr<T> &holdProperty) : property(holdProperty) {}

        Operator op = None; // Node operator (can be null)
        PropertyRef<T> property; // Pointer to property (can be null)
    };

public:
    using Property<T>::Property;

    void addNode(const Node &node) {
        Uint idx = 0;
        if (node.property)
            idx = depends(node.property);
        _expr.push_back(std::make_pair(idx, node));
    }

    void clear(void) {
        for (auto &pair : _expr) {
            if (pair.second.property)
                pair.second.property.disconnect(pair.first);
        }
        _expr.clear();
    }

private:
    Vector<Pair<Uint, Node>> _expr;

    template<typename U>
    Uint depends(Property<U> &other) noexcept {
        return other.connect([this] {
            this->compute();
            return true;
        });
    }

    void compute(void) {
        Stack<T> stack;

        if (_expr.empty())
            throw LogicError("Expression", "Couldn't compute empty expression");
        for (Node &node : _expr) {
            if (node.op != None)
                processOperator(stack, node);
            else
                stack.push(*node.property);
        }
        if (stack.size() != 1)
            throw LogicError("Expression", "Couldn't compute invalid expression");
        Property<T>::set(stack.top());
    }

    void processOperator(Stack<T> &stack, const Node &node) {
        static const UMap<String, ExpressionFct> fcts = {
            { Add, processAddition }, { Sub, processSubstraction },
            { Mult, processMultiplication }, { Div, processDivision }, { Mod, processModulo },
            { Not, processNot }, { And, processAnd }, { Or, processOr },
            { Eq, processEqual }, { Diff, processNotEqual },
            { Sup, processSuperior }, { SupEq, processEqual },
            { Inf, processInferior }, { InfEq, processInferiorEq },
            { If, processTernary }
        };

        fcts[node.op - 1](stack);
    }

    static T extract(Stack<T> &stack) {
            T res;
            if (stack.empty())
                throw LogicError("Expression", "Couldn't compute expression");
            res = stack.top();
            stack.pop();
            return res;
    }

    static void processAddition(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 + op2);
    }

    static void processSubstraction(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 - op2);
    }

    static void processMultiplication(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 * op2);
    }

    static void processDivision(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 / op2);
    }

    static void processModulo(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 % op2);
    }

    static void processNot(Stack<T> &stack) {
        T op1 = extract(stack);
        stack.push(!op1);
    }

    static void processEqual(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 == op2);
    }

    static void processNotEqual(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 != op2);
    }

    static void processAnd(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 && op2);
    }

    static void processOr(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 || op2);
    }

    static void processInferior(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 < op2);
    }

    static void processInferiorEq(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 <= op2);
    }

    static void processSuperior(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 > op2);
    }

    static void processSuperiorEq(Stack<T> &stack) {
        T op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 >= op2);
    }

    static void processTernary(Stack<T> &stack) {
        T op3 = extract(stack), op2 = extract(stack), op1 = extract(stack);
        stack.push(op1 ? op2 : op3);
    }
};