/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** PropertyGen
*/

#pragma once

#define MAKE_PROPERTY_READONLY(type, name) \
private: \
    Property<type> _##name; \
public: \
    const Property<type> &name(void) const noexcept { return _##name.get(); }

#define MAKE_PROPERTY(type, name) \
    MAKE_PROPERTY_READONLY(type, name) \
    void name(const Property<type> &other) { _##name.set(other); }
