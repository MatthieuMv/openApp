/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** tests_Log
*/

#include <criterion/criterion.h>
#include <openApp/Core/Log.hpp>
#include <openApp/Types/SStream.hpp>

Test(Log, Basics)
{
    oA::OSStream os;
    oA::Log log(os);

    log.setEnabled(false);
    log << oA::Repeat(4) << "Hi !" << oA::endl;
    cr_assert(os.str().empty());
    log.setEnabled(true);
    log << "Hello world";
    log.flush();
    cr_assert_eq(os.str(), "Hello world");
}

Test(Log, Repeat)
{
    oA::OSStream os;
    oA::Log log(os);

    log << oA::Repeat(4) << '\t' << oA::Repeat(1) << "123" << oA::Repeat(0) << "42" << oA::endl;
    cr_assert_eq(os.str(), "\t\t\t\t123\n");
}

Test(Log, Colors)
{
    oA::QuoteVector vec = { oA::Quote(oA::CSL_BLUE, '#') };
    oA::OSStream os;
    oA::Log log(os, oA::CSL_RED, vec);
    oA::String res = oA::CSL_RED + oA::CSL_BLUE + "Hello" + oA::CSL_RED;

    log << "#" << "Hello" << "#";
    cr_assert_eq(os.str(), res);
}

Test(Log, Colors2)
{
    oA::OSStream os;
    oA::Log log(os, oA::CSL_RED);
    oA::String res = oA::CSL_RED + "Hello" + oA::CSL_RESET + '\n';

    log << "Hello" << oA::endl;
    cr_assert_eq(os.str(), res);
}

Test(Log, Values)
{
    oA::OSStream os;
    oA::Log log(os);
    bool b = true;
    char c = 'a';
    oA::Double d = 12.2f;
    oA::Long l = 42;
    oA::String res = "truea12.242";

    log << b << c << d << l;
    cr_assert_eq(os.str(), res);
}