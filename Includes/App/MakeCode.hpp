/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** PropertyGen
*/

#pragma once

#include "App/Property.hpp"

/* Makes a readonly property (variable var with getter var()) */
#define MAKE_PROPERTY_READONLY(T, var) \
private: \
    oA::Property<T> _##var; \
public: \
    oA::Property<T> &var(void) noexcept { return _##var; } \
    const oA::Property<T> &var(void) const noexcept { return _##var; } \
    const T &get_##var(void) const noexcept { return _##var.get(); }

/* Makes a property (variable var with getter var() and setter set_var()) */
#define MAKE_PROPERTY(T, var) \
    MAKE_PROPERTY_READONLY(T, var) \
    bool set_##var(const T &value) { return _##var.set(value); }
