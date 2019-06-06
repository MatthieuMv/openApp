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

/**
 * @brief Standard container extender
 *
 * @tparam ContainerType Type of the container
 * @tparam Value Value of Type's container
 */
template<typename ContainerType, typename Value>
class oA::ContainerHelper : public ContainerType
{
public:
    using ContainerType::ContainerType;

    /**
     * @brief Apply a non-const function to every element
     *
     * @tparam Signature Applied function signature
     * @param fct Applied function
     */
    template<typename Signature>
    void apply(const Signature &fct) {
        std::for_each(this->begin(), this->end(), fct);
    }

    /**
     * @brief Apply a const function to every element
     *
     * @tparam Signature Applied function signature
     * @param fct Applied function
     */
    template<typename Signature>
    void apply(const Signature &fct) const {
        std::for_each(this->begin(), this->end(), fct);
    }

    /**
     * @brief Remove every element matching a value
     *
     * @param toRemove Matching value to remove
     */
    void removeIf(const Value &toRemove) {
        auto it = std::remove(this->begin(), this->end(), toRemove);
        this->erase(it, this->end());
    }

    /**
     * @brief Remove every elements matching a predicate
     *
     * @tparam Signature Predicate signature
     * @param predicate Match function (must return a boolean)
     */
    template<typename Signature>
    void removeIf(const Signature &predicate) {
        auto it = std::remove_if(this->begin(), this->end(), predicate);
        this->erase(it, this->end());
    }

    /**
     * @brief Retreive the first non-const element matching the predicate
     *
     * @tparam Signature Predicate signature
     * @param predicate Match function (must return a boolean)
     */
    template<typename Signature>
    auto findIf(const Signature &predicate) {
        return findIf(this->begin(), predicate);
    }

    /**
     * @brief Retreive the first const element matching the predicate
     *
     * @tparam Signature Predicate signature
     * @param predicate Match function (must return a boolean)
     */
    template<typename Signature>
    auto findIf(const Signature &predicate) const {
        return findIf(this->begin(), predicate);
    }

    /**
     * @brief Retreive the first non-const element matching the predicate, starting at given iterator
     *
     * @tparam Iterator Iterator type
     * @tparam Signature Predication signature
     * @param start Begin of search interator
     * @param predicate Match function (must return a boolean)
     * @return Iterator Matching iterator if found
     */
    template<typename Iterator, typename Signature>
    auto findIf(Iterator start, const Signature &predicate) {
        return std::find_if(start, this->end(), predicate);
    }

    /**
     * @brief Retreive the first const element matching the predicate, starting at given iterator
     *
     * @tparam Iterator Iterator type
     * @tparam Signature Predication signature
     * @param start Begin of search interator
     * @param predicate Match function (must return a boolean)
     * @return Iterator Matching iterator if found
     */
    template<typename Iterator, typename Signature>
    auto findIf(Iterator start, const Signature &predicate) const {
        return std::find_if(start, this->end(), predicate);
    }
};