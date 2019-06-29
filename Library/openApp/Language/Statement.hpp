/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Statement
*/

#pragma once

#include <openApp/Types/Scalars.hpp>

namespace oA
{
    enum Statement {
        Block,
        Declaration,
        Condition,
        While,
        For,
        Switch
    };

    struct StatementModel
    {
        Statement type;
    };

    /**
     * @brief Check if a statement exists
     * 
     * @param statement Statement as String
     * @return true Statement is valid
     * @return false Statement is invalid
     */
    bool IsStatement(const String &statement);

    /**
     * @brief Get the StatementModel of a statement's string
     * 
     * @param op Statement as String
     * @return StatementModel& Resulting model
     */
    const StatementModel &GetStatement(const String &statement);
}