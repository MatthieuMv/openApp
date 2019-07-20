/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemFactory
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/App/Item.hpp>

namespace oA { class ItemFactory; }

class oA::ItemFactory
{
public:
    ItemFactory(void) = delete;

    /**
     * @brief Register a new Item derived type into the factory
     * 
     * @tparam T Type to insert
     */
    template<typename T>
    static void Register(void) {
        Components[T().getName()] = [] {
            return ItemPtr(new T);
        };
    }

    /**
     * @brief Check the existence of a name in the factory
     * 
     * @param name Name to check
     * @return true Name exists
     * @return false Name doesn't exists
     */
    static bool Exists(const String &name);

    /**
     * @brief Instanciate a registered type with his name
     * 
     * @param name Name to instanciate
     * @return Item* New item (can be null)
     */
    static ItemPtr Instanciate(const String &name);

    /**
     * @brief Register each openApp base Items if not already done
     */
    static void RegisterBaseItems(void);

private:
    static UMap<String, Function<ItemPtr(void)>> Components;
};