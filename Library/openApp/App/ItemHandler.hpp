/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemHandler
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Containers/Vector.hpp>

namespace oA
{
    namespace ItemUtils { class ItemHandler; }

    class Item;

    /**
     * @brief Pointer to Item
     */
    using ItemPtr = Shared<Item>;
}

class oA::ItemUtils::ItemHandler
{
public:
    /**
     * @brief Destroy the Item Handler object
     */
    virtual ~ItemHandler(void) = default;

    /**
     * @brief Event called when appending a new Item
     */
    virtual void onAppendChild(Item &) {}

    /**
     * @brief Event called when removing an Item
     */
    virtual void onRemoveChild(Item &) {}

    /**
     * @brief Event called when children count changes
     */
    virtual void onSizeChanged(void) {}

    /**
     * @brief Return number of children
     *
     * @return UInt Number of children
     */
    UInt childCount(void) const noexcept { return _children.size(); }

    /**
     * @brief Add a child ItemPtr by copy
     *
     * @param child Value to copy
     */
    Item &appendChild(const ItemPtr &child);

    /**
     * @brief Add a child ItemPtr by move
     *
     * @param child Value to move
     */
    Item &appendChild(ItemPtr &&child);

    /**
     * @brief Remove a child using index
     *
     * @param id Child index
     */
    void removeChild(UInt index);

    /**
     * @brief Remove a child using internal id
     *
     * @param id Matching child id
     */
    void removeChild(const String &id);

    /**
     * @brief Pop last child
     */
    void popChild(void);

    /**
     * @brief Extract a child using index
     *
     * @param id Child index
     * @return ItemPtr Extracted item
     */
    ItemPtr extractChild(UInt index);

    /**
     * @brief Extract a child using internal id
     *
     * @param id Matching child id
     * @return ItemPtr Extracted item
     */
    ItemPtr extractChild(const String &id);

    /**
     * @brief Check existence of a child using internal id
     *
     * @param id Child id to find
     * @return true Child has been found
     * @return false Child hasn't been found
     */
    bool childExists(const String &id) const noexcept;

    /**
     * @brief Return a non-const reference to matching child using index
     *
     * @param index Child index
     * @return Item& Child at index
     */
    Item &getChild(UInt index);

    /**
     * @brief Return a const reference to matching child using index
     *
     * @param index Child index
     * @return Item& Child at index
     */
    const Item &getChild(UInt index) const;

    /**
     * @brief Return a non-const reference to matching child using internal id
     *
     * @param id Child id to find
     * @return Item& Matching child
     */
    Item &getChild(const String &id);

    /**
     * @brief Return a const reference to matching child using internal id
     *
     * @param id Child id to find
     * @return Item& Matching child
     */
    const Item &getChild(const String &id) const;

    /**
     * @brief Return a child pointer using index
     *
     * @param index Child index
     * @return Item& Matching child
     */
    const ItemPtr &getChildPtr(UInt index) const;

    /**
     * @brief Return a child pointer using internal id
     *
     * @param id Child id to find
     * @return Item& Matching child
     */
    const ItemPtr &getChildPtr(const String &id) const;

    /**
     * @brief Returun const reference to children
     *
     * @return const Vector<ItemPtr>& Children vector
     */
    const Vector<ItemPtr> &children(void) const noexcept { return _children; }

    /**
     * @brief Apply a non-const function to children
     *
     * @tparam Signature Function signature
     * @param fct Function
     */
    template<typename Signature>
    void applyToChildren(const Signature &fct) { _children.apply(fct); }

    /**
     * @brief Apply a const function to children
     *
     * @tparam Signature Function signature
     * @param fct Function
     */
    template<typename Signature>
    void applyToChildren(const Signature &fct) const { _children.apply(fct); }

    /**
     * @brief Check if Item class is derived of another class
     *
     * @tparam T Class to check
     * @return true Class can be safely casted
     * @return false Class can't be casted
     */
    template<typename T>
    bool isDerivedOf(void) const noexcept {
        return dynamic_cast<const T *>(this) != nullptr;
    }

protected:
    Vector<ItemPtr> _children;
};