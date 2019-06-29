/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operator
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Containers/Pair.hpp>

namespace oA::RPN
{
    /**
     * @brief Enumeration of Operator types
     */
    enum OperatorType {
        None = 0,
        LeftParenthesis, RightParenthesis, // ( )
        Addition, Substraction, Multiplication, Division, Modulo, // + - * / %
        Not, And, Or, // ! && ||
        Equal, Diff, // == !=
        Superior, SuperiorEqual, Inferior, InferiorEqual, // > >= < <=
        TernaryIf, TernaryElse, // ? :
        Assign, // =
        AdditionAssign, SubstractionAssign, MultiplicationAssign, DivisionAssign, ModuloAssign, // += -= *= /= %=
        Call, // ()
        Separator // ;
    };

    /**
     * @brief Enumeration of Operator flows
     */
    enum OperatorFlow {
        NoneFlow = 0,
        RightToLeft,
        LeftToRight
    };

    /**
     * @brief This const struct is only initialized internally in an OperatorMap
     */
    struct Operator
    {
        const OperatorType type;
        const OperatorFlow flow;
        const UByte priority;
    };

    using OperatorMap = Vector<Pair<String, Operator>>;

    /**
     * @brief Check existence of an operator as String
     *
     * @param op String operator representation
     * @return true Operator exists
     * @return false Operator doesn't exists
     */
    bool OperatorExists(const String &op);

    /**
     * @brief Get an Operator with its String representation
     *
     * @param op String operator representation
     * @return const Operator& Found operator
     */
    const Operator &GetOperator(const String &op);

    /**
     * @brief Format given String expression, adding space if needed between operators
     *
     * @param expr Expression to format
     */
    void FormatExpression(String &expr);

    /**
     * @brief Get an Operator String representation
     *
     * @param op Asked operator
     * @return String Operator representation
     */
    String GetOperatorString(OperatorType op);
}