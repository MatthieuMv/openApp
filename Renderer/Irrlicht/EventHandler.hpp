/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** EventHandler
*/

#pragma once

// IrrlichtContext
#include "IrrlichtContext.hpp"

class EventHandler : public irr::IEventReceiver
{
public:
    EventHandler(IrrlichtContext &context);

    virtual bool OnEvent(const irr::SEvent &event);

private:
    IrrlichtContext &_context;

    void convertMouseEvent(oA::Event &target, const irr::SEvent &event);
    void convertKeyboardEvent(oA::Event &target, const irr::SEvent &event);
    oA::Key convertKey(irr::EKEY_CODE code) const noexcept;
};