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
    const T &var(void) const noexcept { return _##var(); }

/* Makes a property (variable var with getter var() and setter set_var()) */
#define MAKE_PROPERTY(T, var) \
    MAKE_PROPERTY_READONLY(T, var) \
    void set_##var(const T &value) { _##var = value; }
