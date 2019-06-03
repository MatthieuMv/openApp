/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Error
*/

#pragma once

#include "Types/String.hpp"

namespace oA
{
    class Error;
    class CastError;
}

class oA::Error : public std::exception
{
public:
    Error(const String &msg) : _msg(msg) {}
    Error(const String &from, const String &msg) : _msg("#" + from + ":# " + msg) {}

    virtual const char *what(void) const noexcept { return _msg.c_str(); }

private:
    String _msg;
};

class oA::CastError : public oA::Error { public: using Error::Error; };