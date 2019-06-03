/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_ContainerHelper
*/

#include <criterion/criterion.h>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Containers/Vector.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Containers/List.hpp>

Test(ContainerHelper, Apply)
{
    oA::UMap<oA::Int, oA::Int> map = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }
    }, res = {
        { 0, 0 }, { 1, 2 }, { 2, 4 }
    };
    const auto &ref(map);

    map.apply([](auto &v) { cr_assert((v.first + 1) == v.second); v.second = v.first * 2; });
    ref.apply([](const auto &v) { cr_assert((v.first * 2) == v.second); });
    cr_assert_eq(map, res);
}

Test(ContainerHelper, RemoveIf)
{
    oA::Vector<oA::Int> vector = { 0, 1, 2, 3, 4 };
    oA::Vector<oA::Int> res = { 2, 4 };

    cr_assert_eq(vector.size(), 5);
    vector.removeIf(0);
    cr_assert_eq(vector.size(), 4);
    vector.removeIf([](auto x) { return x % 2; });
    cr_assert_eq(vector.size(), 2);
    cr_assert_eq(vector, res);
}

Test(ContainerHelper, FindIf)
{
    auto predicate = [](const oA::Int &x) { return !(x % 2); };
    oA::List<oA::Int> list = {
        0, 1, 2, 3, 4
    }, res = { 0, 1, 42, 3, 42 };
    const auto &ref(list);
    auto it = list.findIf(predicate);
    auto it2 = ref.findIf(predicate);

    cr_assert_eq(*it, 0);
    cr_assert_eq(*it, *it2);
    while (it != list.end() && it2 != ref.end()) {
        it = list.findIf(++it, predicate);
        it2 = ref.findIf(++it2, predicate);
        if (it != list.end()) {
            cr_assert_eq(*it, *it2);
            *it = 42;
        }
    }
    cr_assert_eq(list, res);
}