/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Error
*/

#pragma once

#include "String.hpp"
#include <stdexcept>

namespace oA
{
    class Error;
    class RuntimeError;
    class SyntaxError;
    class TypeError;
    class LogicError;
}

class oA::Error : public std::exception
{
public:
    Error(const String &msg) : _msg(msg) {}
    Error(const String &from, const String &msg)
    : _msg("@" + from + ":@ " + msg) {}

    virtual const char *what(void) const noexcept { return _msg.c_str(); }

private:
    String _msg;
};

class oA::RuntimeError : public oA::Error
{
public:
    using Error::Error;
};

class oA::SyntaxError : public oA::Error
{
public:
    using Error::Error;
};

class oA::TypeError : public oA::Error
{
public:
    using Error::Error;
};

class oA::LogicError : public oA::Error
{
public:
    using Error::Error;
};
