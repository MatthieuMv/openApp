/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_String
*/

#include <criterion/criterion.h>
#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>

Test(String, Basics)
{
    oA::String toCopy("Hello"), toMove("World"), tmp("42");
    oA::String str, copy(toCopy), move(std::move(toMove));

    cr_assert(str.empty());
    cr_assert(!str);
    str = oA::String('z') + oA::String("aze");
    str += tmp;
    cr_assert_eq(str, "zaze42");
    str += oA::String("0");
    cr_assert_eq(str, "zaze420");
    str = tmp;
    cr_assert_eq(str, "42");
    str = oA::String("42");
    cr_assert_eq(str, "42");
    cr_assert_eq(copy, "Hello");
    cr_assert_eq(move, "World");
    str = copy + " " + move;
    cr_assert_eq(str, "Hello World");
}

Test(String, BasicsWithStd)
{
    std::string toCopy("Hello"), toMove("World");
    oA::String str, copy(toCopy), move(std::move(toMove));

    cr_assert(str.empty());
    cr_assert_eq(copy, "Hello");
    cr_assert_eq(move, "World");
    str = copy + " " + move;
    cr_assert_eq(str, "Hello World");
}

Test(String, BasicsWithRaw)
{
    const char *toCopy = "Hello", *toUse = "World";
    oA::String str, copy(toCopy), other(toUse);

    cr_assert(str.empty());
    cr_assert_eq(copy, "Hello");
    cr_assert_eq(other, "World");
    str = copy + " " + other;
    cr_assert_eq(str, "Hello World");
}

Test(String, BooleanCast)
{
    oA::String str = "false";
    bool crashed = false;

    cr_assert(str.isBoolean());
    cr_assert_not(str.toBool());
    str = "true";
    cr_assert(str.isBoolean());
    cr_assert(str.toBool());
    str = "123";
    cr_assert_not(str.isBoolean());
    try { str.toBool(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(String, SignedCast)
{
    oA::String str = "-42";
    bool crashed = false;

    cr_assert(str.isSigned());
    cr_assert_eq(str.toInt(), -42);
    str = "-4z.2";
    cr_assert_not(str.isSigned());
    try { str.toInt(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(String, UnsignedCast)
{
    oA::String str = "42";
    bool crashed = false;

    cr_assert(str.isUnsigned());
    cr_assert_eq(str.toUint(), 42);
    str = "-42z";
    cr_assert_not(str.isUnsigned());
    try { str.toUint(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(String, DecimalCast)
{
    oA::String str = "42.5";
    bool crashed = false;

    cr_assert(str.isDecimal());
    cr_assert_float_eq(str.toFloat(), 42.5f, 0.0001f);
    cr_assert_float_eq(str.toDouble(), 42.5f, 0.0001f);
    str = "-42.2.3";
    cr_assert_not(str.isDecimal());
    str = "-42.z";
    cr_assert_not(str.isDecimal());
    try { str.toFloat(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
    crashed = false;
    try { str.toDouble(); }
    catch (...) { crashed = true; }
    cr_assert(crashed);
}

Test(String, replace)
{
    oA::String str("Th1s 1s 4 20");

    str.replace("1", "i");
    str.replace("4", "four");
    str.replace("20", "twenty");
    cr_assert_eq(str, "This is four twenty");
}

Test(String, replaceWith)
{
    oA::String str("X X X X");
    char c = 'a' - 1;

    str.replaceWith("X", [&c] {
        return ++c;
    });
    cr_assert_eq(str, "a b c d");
}

Test(String, ToString)
{
    cr_assert_eq(oA::ToString(42), "42");
    cr_assert_eq(oA::ToString(42.4242), "42.4242");
    cr_assert_eq(oA::ToString(42.0f), "42");
}

Test(String, Comparison)
{
    oA::String str("Hello world");

    cr_assert(str.startWith("Hello"));
    cr_assert(str.endWith("world"));
    cr_assert_not(str.endWith("Hello world !"));
}

Test(String, TryAppend)
{
    oA::String str("file");

    str.tryAppend(".oA");
    cr_assert_eq(str, "file.oA");
    str.tryAppend(".oA");
    cr_assert_eq(str, "file.oA");
}