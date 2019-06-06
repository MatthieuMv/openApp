/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Error
*/

#pragma once

#include <openApp/Types/String.hpp>

namespace oA
{
    class Error;
    class CastError;
    class LogicError;
}

/**
 * @brief Error exception base
 */
class oA::Error : public std::exception
{
public:
    /**
     * @brief Construct a new Error object with an error message
     *
     * @param msg Error message
     */
    Error(const String &msg) : _msg(msg) {}

    /**
     * @brief Construct a new Error object with a quoted source and an error message
     *
     * @param from Source
     * @param msg Error message
     */
    Error(const String &from, const String &msg) : _msg("#" + from + ":# " + msg) {}

    /**
     * @brief Return internal message
     *
     * @return const char* Error message
     */
    virtual const char *what(void) const noexcept { return _msg.c_str(); }

private:
    String _msg;
};

/**
 * @brief Used on casting error
 */
class oA::CastError : public oA::Error { public: using Error::Error; };

/**
 * @brief Used on function implicit logic error
 */
class oA::LogicError : public oA::Error { public: using Error::Error; };