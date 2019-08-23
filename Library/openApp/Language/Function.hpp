/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Function
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>

namespace oA::Lang
{
    /**
     * @brief Enum containing every implemented Function
     */
    enum Function {
        ToNumber,
        ToLiteral,
        ToContainer,
        Length,
        Push,
        Pop,
        Insert,
        Remove,
        Print
    };

    /**
     * @brief Model which contains informations about an Function
     */
    struct FunctionModel
    {
        Function type;
        Int args;
    };

    /**
     * @brief Check if an Function exists
     *
     * @param op Function as String
     * @return true Function is valid
     * @return false Function is invalid
     */
    bool IsFunction(const String &op);

    /**
     * @brief Get the FunctionModel of an Function's string
     *
     * @param op Function as String
     * @return FunctionModel& Resulting model
     */
    const FunctionModel &GetFunction(const String &op);

    /**
     * @brief Get the FunctionModel of an Function's type
     *
     * @param op Function as type
     * @return FunctionModel& Resulting model
     */
    const FunctionModel &GetFunction(Function statement);

    /**
     * @brief Get the Symbol String of an Function
     *
     * @param op Function to retreive
     * @return const String Resulting symbol
     */
    const String &GetFunctionSymbol(Function statement);
}