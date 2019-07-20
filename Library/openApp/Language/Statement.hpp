/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Statement
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>

namespace oA::Lang
{
    /**
     * @brief Enum containing every implemented Statement 
     */
    enum Statement {
        If,
        Else,
        Switch,
        Case,
        While,
        For,
        Break,
        Return
    };

    /**
     * @brief Model which contains informations about an Statement
     */
    struct StatementModel
    {
        Statement type;
    };

    /**
     * @brief Check if an Statement exists
     * 
     * @param op Statement as String
     * @return true Statement is valid
     * @return false Statement is invalid
     */
    bool IsStatement(const String &op);

    /**
     * @brief Get the StatementModel of an Statement's string
     * 
     * @param op Statement as String
     * @return StatementModel& Resulting model
     */
    const StatementModel &GetStatement(const String &op);

    /**
     * @brief Get the StatementModel of an Statement's type
     * 
     * @param op Statement as type
     * @return StatementModel& Resulting model
     */
    const StatementModel &GetStatement(Statement statement);

    /**
     * @brief Get the Symbol String of an Statement
     * 
     * @param op Statement to retreive
     * @return const String Resulting symbol
     */
    const String &GetStatementSymbol(Statement statement);
}