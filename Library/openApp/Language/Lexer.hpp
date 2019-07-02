/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#pragma once

#include <openApp/Types/Stream.hpp>
#include <openApp/Core/GetLine.hpp>

namespace oA::Lang { class Lexer; }

class oA::Lang::Lexer
{
public:
    virtual ~Lexer(void) = default;
    Lexer(IStream &ss) : _ss(ss) {}

    String &token(void) noexcept { return _token; }
    const String &token(void) const noexcept { return _token; }

    IStream &ss(void) noexcept { return _ss; }
    const IStream &ss(void) const noexcept { return _ss; }

    bool readToken(void) { return (_ss >> _token).operator bool(); }
    bool readLine(char delim = '\n') { return GetLine(_ss, _token, delim); }

    void processUnit(const String &end = '\0');
    void captureExpression(void);

    virtual void interpretToken(void) = 0;

protected:
    String _token;
    IStream &_ss;

private:
    bool matchBrackets(void) const noexcept;
};