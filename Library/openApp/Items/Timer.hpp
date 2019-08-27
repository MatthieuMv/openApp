/*
** EPITECH PROJECT, 2019
** TeamfightArena
** File description:
** Timer
*/

#pragma once

#include <openApp/Core/LightChrono.hpp>
#include <openApp/Items/Item.hpp>

namespace oA { class Timer; }

class oA::Timer : virtual public Item
{
public:
    virtual ~Timer(void) = default;

    Timer(void) {
        auto &running = append("running") = false; // Running state, if changed will call associated start / stop function
        append("repeat") = false; // If true will repeat timer forever
        append("interval") = 0; // Duration before trigger in milliseconds
        append("triggered"); // Event called on triggered
        running.connect([this] { _ch.reset(); return true; });
    }

    virtual String getName(void) const noexcept { return "Timer"; }

    virtual void onUpdate(IRenderer &) {
        if (!get("running") || _ch.getMilliseconds() < getAs<Number>("interval"))
            return;
        if (!get("repeat"))
            get("running") = false;
        else
            _ch.reset();
        get("triggered").call();
    }
private:
    LightChrono _ch;
};