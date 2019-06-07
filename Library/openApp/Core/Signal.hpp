/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Signal
*/

#pragma once

#include <openApp/Types/Error.hpp>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/Function.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/UMap.hpp>

namespace oA { template<typename... Args> class Signal; }

/**
 * @brief A lightweight Signal class that contains Slot functionscalled on emit (can't be copied)
 *
 * @tparam Args Parameters types to be passed in Slot's argument
 */
template<typename... Args>
class oA::Signal
{
public:
    /**
     * @brief Signal's Slot function signature
     */
    using Slot = oA::Function<bool(Args...)>;

    /**
     * @brief Construct a new Signal object
     */
    Signal(void) = default;

    /**
     * @brief Destroy the Signal object
     */
    virtual ~Signal(void) = default;

    /**
     * @brief Construct a new Signal object by move
     *
     * @param other Value to move
     */
    Signal(Signal &&other) { swap(other); }

    /**
     * @brief Move assignement operator
     *
     * @param other Value to move
     * @return Signal& Allow chain operators
     */
    Signal &operator=(Signal &&other) {
        swap(other);
        return *this;
    }

    /**
     * @brief Signal can't be copied, it should be moved
     */
    Signal(const Signal &) = delete;

    /**
     * @brief Signal can't be copied, it should be moved
     */
    Signal &operator=(const Signal &) = delete;

    /**
     * @brief Connect a Slot, returning its index
     *
     * @param slot Slot to be connected
     * @return Uint Index used for disconnexion
     */
    Uint connect(Slot &&slot) noexcept {
        _slots.insert(std::make_pair(++_index, std::move(slot)));
        return _index;
    }

    /**
     * @brief Disconnect a Slot
     *
     * @param index Index of the slot to be disconnected
     */
    void disconnect(Uint index) {
        auto it = _slots.find(index);
        if (it == _slots.end())
            throw AccessError("Signal", "Disconnection index not found @" + oA::ToString(index) + "@");
        _slots.erase(it);
    }

    /**
     * @brief Call every active Slot, and remove them on false return
     *
     * @param args Slot call arguments
     */
    virtual void emit(Args ...args) const {
        for (auto it = _slots.begin(); it != _slots.end();) {
            if (!it->second(args...))
                it = _slots.erase(it);
            else
                ++it;
        }
    }

    /**
     * @brief Swap two signals
     *
     * @param other Value to swap
     */
    void swap(Signal &other) noexcept {
        _slots.swap(other._slots);
        std::swap(_index, other._index);
    }

private:
    mutable UMap<Uint, Slot> _slots; // Should be mutable to preserve emit constness
    Uint _index = 0;
};