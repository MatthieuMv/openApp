/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ContainerHelper
*/

#pragma once

// Standard algorithms
#include <algorithm>

namespace oA { template<typename Type, typename Value> class ContainerHelper; }

template<typename ContainerType, typename Value>
class oA::ContainerHelper : public ContainerType
{
public:
    using ContainerType::ContainerType;

    /* Apply a non-const function to every element */
    template<typename Signature>
    void apply(const Signature &fct) {
        std::for_each(this->begin(), this->end(), fct);
    }

    /* Apply a const function to every element */
    template<typename Signature>
    void apply(const Signature &fct) const {
        std::for_each(this->begin(), this->end(), fct);
    }

    /* Remove every elements matching toRemove value */
    void removeIf(const Value &toRemove) {
        auto it = std::remove(this->begin(), this->end(), toRemove);
        this->erase(it, this->end());
    }

    /* Remove every elements matching the predicate */
    template<typename Signature>
    void removeIf(const Signature &predicate) {
        auto it = std::remove_if(this->begin(), this->end(), predicate);
        this->erase(it, this->end());
    }

    /* Retreive the first non-const element matching the predicate */
    template<typename Signature>
    auto findIf(const Signature &predicate) {
        return findIf(this->begin(), predicate);
    }

    /* Retreive the first const element matching the predicate */
    template<typename Signature>
    auto findIf(const Signature &predicate) const {
        return findIf(this->begin(), predicate);
    }

    /* Retreive the first non-const element matching the predicate, staring at given iterator */
    template<typename Iterator, typename Signature>
    auto findIf(Iterator start, const Signature &predicate) {
        return std::find_if(start, this->end(), predicate);
    }

    /* Retreive the first const element matching the predicate, staring at given iterator */
    template<typename Iterator, typename Signature>
    auto findIf(Iterator start, const Signature &predicate) const {
        return std::find_if(start, this->end(), predicate);
    }
};