/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operator
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Types/V2.hpp>

namespace oA::Lang
{
    /**
     * @brief Enum containing every implemented operator 
     */
    enum Operator {
        Not, Equal, Different,
        Superior, SuperiorEqual, Inferior, InferiorEqual,
        Addition, Substraction, Multiplication, Division, Modulo,
        Assign, AdditionAssign, SubstractionAssign, MultiplicationAssign, DivisionAssign, ModuloAssign,
        PrefixIncrement, PrefixDecrement, SufixIncrement, SufixDecrement,
        Call, At,
        Comma, End,
        TernaryIf, TernaryElse,
        LeftParenthese, RightParenthese,
        LeftBracket, RightBracket,
        LeftBrace, RightBrace
    };

    enum Associativity {
        NoneAssociativity,
        LeftToRight,
        RightToLeft
    };

    /**
     * @brief Model which contains informations about an operator
     */
    struct OperatorModel
    {
        Operator type;
        Uint args;
        Uint precedence;
        Associativity associativity;
    };

    /**
     * @brief Check if an operator exists
     * 
     * @param op Operator as String
     * @return true Operator is valid
     * @return false Operator is invalid
     */
    bool IsOperator(const String &op);

    /**
     * @brief Get the OperatorModel of an operator's string
     * 
     * @param op Operator as String
     * @return OperatorModel& Resulting model
     */
    const OperatorModel &GetOperator(const String &op);

    /**
     * @brief Get the OperatorModel of an operator's type
     * 
     * @param op Operator as type
     * @return OperatorModel& Resulting model
     */
    const OperatorModel &GetOperator(Operator op);

    /**
     * @brief Get the Symbol String of an Operator
     * 
     * @param op Operator to retreive
     * @return const String Resulting symbol
     */
    const String &GetOperatorSymbol(Operator op);
}