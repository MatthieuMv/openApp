/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ExpressionStack
*/

#pragma once

// Stack
#include "Core/Stack.hpp"
// UMap
#include "Core/UMap.hpp"
// ExpressionNode
#include "Core/ExpressionNode.hpp"

namespace oA { template<typename T> class ExpressionStack; }

template<typename T>
class oA::ExpressionStack : public Stack<ExpressionNode<T>>
{
public:
    using ExpressionFct = Function<void(ExpressionStack<T> &)>;

    void processOperator(OperatorType op) {
        static const UMap<Uint, ExpressionFct> fcts = {
            { Addition, ProcessAddition }, { Substraction, ProcessSubstraction },
            { Multiplication, ProcessMultiplication }, { Division, ProcessDivision }, { Modulo, ProcessModulo },
            { Not, ProcessNot }, { And, ProcessAnd }, { Or, ProcessOr },
            { Equal, ProcessEqual }, { Diff, ProcessNotEqual },
            { Superior, ProcessSuperior }, { SuperiorEqual, ProcessEqual },
            { Inferior, ProcessInferior }, { InferiorEqual, ProcessInferiorEq },
            { If, ProcessTernary },
            { Assign, ProcessAssign },
            { AdditionAssign, ProcessAdditionAssign }, { SubstractionAssign, ProcessSubstractionAssign },
            { MultiplicationAssign, ProcessMultiplicationAssign }, { DivisionAssign, ProcessDivisionAssign }, { ModuloAssign, ProcessModuloAssign },
            { Call, ProcessCall },
            { Separator, ProcessSeparator }
        };

        auto f = fcts.find(op);
        if (f != fcts.end())
            return f->second(*this);
        throw LogicError("Expression", "Couldn't find operator processing function @" + ToString(op) + "@");
    }

    void extract(ExpressionNode<T> &target) {
        if (this->empty())
            throw LogicError("Expression", "Can't extract value from @empty stack@");
        target = std::move(this->top());
        this->pop();
    }

    T extractValue(void) {
        ExpressionNode<T> res;
        extract(res);
        if (res.isExpression())
            return res.getExpression()->get();
        else if (res.isValue())
            return res.getValue();
        throw LogicError("Expression", "Can't extract value from @OperatorNode@");
    }

    ExpressionPtr<T> extractExpression(void) {
        ExpressionNode<T> res;
        extract(res);
        if (!res.isExpression())
            throw LogicError("Expression", "Can't extract @property@");
        return res.getExpression();
    }

private:
    static void ProcessAddition(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 + op2);
    }

    static void ProcessSubstraction(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 - op2);
    }

    static void ProcessMultiplication(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 * op2);
    }

    static void ProcessDivision(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 / op2);
    }

    static void ProcessModulo(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 % op2);
    }

    static void ProcessNot(ExpressionStack<T> &stack) {
        auto op = stack.extractValue();
        stack.push(T(!op));
    }

    static void ProcessEqual(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 == op2));
    }

    static void ProcessNotEqual(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 != op2));
    }

    static void ProcessAnd(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 && op2));
    }

    static void ProcessOr(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 || op2));
    }

    static void ProcessInferior(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 < op2));
    }

    static void ProcessInferiorEq(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 <= op2));
    }

    static void ProcessSuperior(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 > op2));
    }

    static void ProcessSuperiorEq(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(T(op1 >= op2));
    }

    static void ProcessTernary(ExpressionStack<T> &stack) {
        auto op3 = stack.extractValue(), op2 = stack.extractValue(), op1 = stack.extractValue();
        stack.push(op1 ? op2 : op3);
    }

    static void ProcessAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op2);
        stack.push(op1);
    }

    static void ProcessAdditionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op1->get() + op2);
        stack.push(op1);
    }

    static void ProcessSubstractionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op1->get() - op2);
        stack.push(op1);
    }

    static void ProcessMultiplicationAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op1->get() * op2);
        stack.push(op1);
    }

    static void ProcessDivisionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op1->get() / op2);
        stack.push(op1);
    }

    static void ProcessModuloAssign(ExpressionStack<T> &stack) {
        T op2 = stack.extractValue();
        auto op1 = stack.extractExpression();
        op1->set(op1->get() % op2);
        stack.push(op1);
    }

    static void ProcessCall(ExpressionStack<T> &stack) {
        auto op = stack.extractExpression();
        op->compute();
        stack.push(op);
    }

    static void ProcessSeparator(ExpressionStack<T> &stack) {
        ExpressionNode<T> last;
        stack.extract(last);
        while (!stack.empty())
            stack.pop();
        stack.push(std::move(last));
    }
};