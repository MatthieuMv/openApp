/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#include <iostream>
#include "Core/Log.hpp"

const oA::Log oA::cout(oA::Log::COUT);
const oA::Log oA::cerr(oA::Log::CERR);
const oA::Log::Repeater oA::repeat;
const oA::Log::Endl oA::endl;

oA::Log::Log(Output out) : _stream(out == CERR ? std::cerr : std::cout) {}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Repeater &repeater)
{
    log.setRepeat(repeater.get());
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Endl &endl)
{
    (void)(endl);
    if (!log.getEnabled())
        return (log);
    log.getStream() << std::endl;
    return (log);
}