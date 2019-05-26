/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operators
*/

#pragma once

// Uint
#include "Core/Scalar.hpp"
// String
#include "Core/String.hpp"
// Vector
#include "Core/Vector.hpp"
// Pair
#include "Core/Pair.hpp"

namespace oA
{
    enum OperatorType {
        None = 0,
        LeftParenthesis, RightParenthesis, // ( )
        Addition, Substraction, Multiplication, Division, Modulo, // + - * / %
        Not, And, Or, // ! && ||
        Equal, Diff, // == !=
        Superior, SuperiorEqual, Inferior, InferiorEqual, // > >= < <=
        If, Else, // ? :
        Assign, // =
        AdditionAssign, SubstractionAssign, MultiplicationAssign, DivisionAssign, ModuloAssign, // += -= *= /= %=
        Call, // ()
        Separator // ;
    };

    enum OperatorFlow {
        NoneFlow = 0,
        RightToLeft,
        LeftToRight
    };

    struct Operator
    {
        const OperatorType type;
        const OperatorFlow flow;
        const UByte priority;
    };

    using OperatorMap = Vector<Pair<String, Operator>>;

    bool OperatorExists(const String &op);
    const Operator &GetOperator(const String &op);
    void FormatExpression(String &expr);
    String GetOperatorString(OperatorType op);
}