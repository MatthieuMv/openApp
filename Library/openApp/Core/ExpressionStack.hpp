/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ExpressionStack
*/

#pragma once

namespace oA { template <typename T> class ExpressionStack; }

#include <openApp/Types/Error.hpp>
#include <openApp/Containers/List.hpp>
#include <openApp/Core/ExpressionNode.hpp>

/**
 * @brief This class is used to compute an Expression
 *
 * @tparam T Type of the Expression
 */
template<typename T>
class oA::ExpressionStack
{
    using ExpressionFct = Function<void(ExpressionStack<T> &)>;

public:

    /**
     * @brief Push a copied ExpressioNode to the stack
     *
     * @param node ExpressioNode to be pushed
     */
    void push(const ExpressionNode<T> &node) noexcept {
        _stack.push_back(node);
    }

    /**
     * @brief Pop an ExpressionNode from the stack
     *
     * @return ExpressionNode Return removed node
     */
    ExpressionNode<T> pop(void) {
        if (empty())
            throw AccessError("ExpressionStack", "Can't pop @empty@ stack");
        auto it = _stack.begin();
        auto n(std::move(*it));
        _stack.erase(it);
        return n;
    }

    /**
     * @brief Get stack top element
     *
     * @return ExpressionNode<T>& Top element
     */
    ExpressionNode<T> &top(void) {
        if (empty())
            throw AccessError("ExpressionStack", "Can't get top of @empty@ stack");
        return _stack.back();
    }

    /**
     * @brief Return internal stack state
     *
     * @return bool True if stack is empty
     */
    bool empty(void) const noexcept { return _stack.empty(); }

    /**
     * @brief Process a given operator with current stack
     *
     * @param op Operator to process
     */
    void processOperator(RPN::OperatorType op) {
        static const UMap<Uint, ExpressionFct> fcts = {
            { RPN::Addition, ProcessAddition }, { RPN::Substraction, ProcessSubstraction },
            { RPN::Multiplication, ProcessMultiplication }, { RPN::Division, ProcessDivision }, { RPN::Modulo, ProcessModulo },
            { RPN::Not, ProcessNot }, { RPN::And, ProcessAnd }, { RPN::Or, ProcessOr },
            { RPN::Equal, ProcessEqual }, { RPN::Diff, ProcessNotEqual },
            { RPN::Superior, ProcessSuperior }, { RPN::SuperiorEqual, ProcessEqual },
            { RPN::Inferior, ProcessInferior }, { RPN::InferiorEqual, ProcessInferiorEq },
            { RPN::If, ProcessTernary },
            { RPN::Assign, ProcessAssign },
            { RPN::AdditionAssign, ProcessAdditionAssign }, { RPN::SubstractionAssign, ProcessSubstractionAssign },
            { RPN::MultiplicationAssign, ProcessMultiplicationAssign }, { RPN::DivisionAssign, ProcessDivisionAssign }, { RPN::ModuloAssign, ProcessModuloAssign },
            { RPN::Call, ProcessCall },
            { RPN::Separator, ProcessSeparator }
        };

        auto f = fcts.find(op);
        if (f != fcts.end())
            return f->second(*this);
        throw LogicError("Expression", "Couldn't find operator processing function @" + ToString(op) + "@");
    }

private:
    List<ExpressionNode<T>> _stack;

    /**
     * @brief Pop a T value from the stack
     *
     * @return T Return removed node value
     */
    T popValue(void) { return pop().getValue(); }

    /**
     * @brief Pop a Expression<T> ref from the stack
     *
     * @return T Return removed node value
     */
    Shared<Expression<T>> popExpression(void) { return pop().getExpression(); }

    static void ProcessAddition(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 + op2);
    }

    static void ProcessSubstraction(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 - op2);
    }

    static void ProcessMultiplication(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 * op2);
    }

    static void ProcessDivision(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 / op2);
    }

    static void ProcessModulo(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 % op2);
    }

    static void ProcessNot(ExpressionStack<T> &stack) {
        auto op = stack.popValue();
        stack.push(T(!op));
    }

    static void ProcessEqual(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 == op2));
    }

    static void ProcessNotEqual(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 != op2));
    }

    static void ProcessAnd(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 && op2));
    }

    static void ProcessOr(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 || op2));
    }

    static void ProcessInferior(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 < op2));
    }

    static void ProcessInferiorEq(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 <= op2));
    }

    static void ProcessSuperior(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 > op2));
    }

    static void ProcessSuperiorEq(ExpressionStack<T> &stack) {
        T op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(T(op1 >= op2));
    }

    static void ProcessTernary(ExpressionStack<T> &stack) {
        auto op3 = stack.popValue(), op2 = stack.popValue(), op1 = stack.popValue();
        stack.push(op1 ? op2 : op3);
    }

    static void ProcessAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op2);
    }

    static void ProcessAdditionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op1->get() + op2);
    }

    static void ProcessSubstractionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op1->get() - op2);
    }

    static void ProcessMultiplicationAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op1->get() * op2);
    }

    static void ProcessDivisionAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op1->get() / op2);
    }

    static void ProcessModuloAssign(ExpressionStack<T> &stack) {
        T op2 = stack.popValue();
        auto op1 = stack.top().getExpression();
        op1->set(op1->get() % op2);
    }

    static void ProcessCall(ExpressionStack<T> &stack) {
        stack.top().getExpression()->call();
    }

    static void ProcessSeparator(ExpressionStack<T> &stack) {
        auto last = stack.pop();
        while (!stack.empty())
            stack.pop();
        stack.push(std::move(last));
    }
};