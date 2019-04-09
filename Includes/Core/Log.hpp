/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#pragma once

#include "Scalar.hpp"
#include "Stream.hpp"

namespace oA { class Log; }

class oA::Log
{
public:
    class Repeater;
    class Endl;

    enum Output {
        COUT = 0,
        CERR
    };

    Log(Output out = COUT);

    OStream &getStream(void) const noexcept { return _stream; }

    Bool repeat(void) const noexcept { return _repeat ? --_repeat, true : false;; }
    void setRepeat(Uint value) const noexcept { _repeat = value; }

    Bool getEnabled(void) const noexcept { return _enabled; }
    void setEnabled(Bool value) noexcept { _enabled = value; }

    template<typename T>
    const Log &log(const T &value) const noexcept {
        if (!getEnabled())
            return (*this);
        do {
            getStream() << value;
        } while (repeat());
        return (*this);
    }

private:
    OStream &_stream;
    mutable Uint _repeat = 0;
    Bool _enabled = true;
};

class oA::Log::Repeater
{
public:
    Repeater(void) = default;

    const Repeater &operator()(int x) const noexcept {
        _x = x;
        return (*this);
    }

    Uint get(void) const noexcept { return _x; }
private:
    mutable Uint _x = 0;
};

class oA::Log::Endl
{
};

template<typename T>
const oA::Log &operator<<(const oA::Log &log, const T &value) {
    log.log(value);
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Repeater &repeater);
const oA::Log &operator<<(const oA::Log &log, const oA::Log::Endl &endl);

namespace oA
{
    extern const oA::Log cout;
    extern const oA::Log cerr;
    extern const oA::Log::Repeater repeat;
    extern const oA::Log::Endl endl;
}