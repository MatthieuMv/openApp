/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Terminal
*/

#pragma once

#include <openApp/Types/String.hpp>

#if !defined(WIN32) && !defined(_WIN32) && !defined(OA_NO_COLOR)
    #define CONSOLE_HAS_COLOR
#endif

namespace oA
{
    /**
     * @brief Console colors are internal console-interpreted commands of ASCI rendering
     */
    using ConsoleColor = oA::String;

    inline const ConsoleColor CSL_RESET = "\e[0m";

    inline const ConsoleColor CSL_BOLD = "\e[1m";
    inline const ConsoleColor CSL_DIM = "\e[2m";
    inline const ConsoleColor CSL_UNDERLINED = "\e[4m";
    inline const ConsoleColor CSL_BLINK = "\e[5m";
    inline const ConsoleColor CSL_INVERTED = "\e[7m";
    inline const ConsoleColor CSL_HIDDEN = "\e[8m";

    inline const ConsoleColor CSL_DEFAULT = "\e[39m";
    inline const ConsoleColor CSL_BLACK = "\e[30m";
    inline const ConsoleColor CSL_RED = "\e[31m";
    inline const ConsoleColor CSL_GREEN = "\e[32m";
    inline const ConsoleColor CSL_YELLOW = "\e[33m";
    inline const ConsoleColor CSL_BLUE = "\e[34m";
    inline const ConsoleColor CSL_MAGENTA = "\e[35m";
    inline const ConsoleColor CSL_CYAN = "\e[36m";
    inline const ConsoleColor CSL_LIGHT_GRAY = "\e[37m";
    inline const ConsoleColor CSL_DARK_GRAY = "\e[90m";
    inline const ConsoleColor CSL_LIGHT_RED = "\e[91m";
    inline const ConsoleColor CSL_LIGHT_GREEN = "\e[92m";
    inline const ConsoleColor CSL_LIGHT_YELLOW = "\e[93m";
    inline const ConsoleColor CSL_LIGHT_BLUE = "\e[94m";
    inline const ConsoleColor CSL_LIGHT_MAGENTA = "\e[95m";
    inline const ConsoleColor CSL_LIGHT_CYAN = "\e[96m";
    inline const ConsoleColor CSL_WHITE = "\e[97m";

    inline const ConsoleColor CSL_BG_DEFAULT = "\e[49m";
    inline const ConsoleColor CSL_BG_BLACK = "\e[40m";
    inline const ConsoleColor CSL_BG_RED = "\e[41m";
    inline const ConsoleColor CSL_BG_GREEN = "\e[42m";
    inline const ConsoleColor CSL_BG_YELLOW = "\e[43m";
    inline const ConsoleColor CSL_BG_BLUE = "\e[44m";
    inline const ConsoleColor CSL_BG_MAGENTA = "\e[45m";
    inline const ConsoleColor CSL_BG_CYAN = "\e[46m";
    inline const ConsoleColor CSL_BG_LIGHT_GRAY = "\e[47m";
    inline const ConsoleColor CSL_BG_DARK_GRAY = "\e[100m";
    inline const ConsoleColor CSL_BG_LIGHT_RED = "\e[101m";
    inline const ConsoleColor CSL_BG_LIGHT_GREEN = "\e[102m";
    inline const ConsoleColor CSL_BG_LIGHT_YELLOW = "\e[103m";
    inline const ConsoleColor CSL_BG_LIGHT_BLUE = "\e[104m";
    inline const ConsoleColor CSL_BG_LIGHT_MAGENTA = "\e[105m";
    inline const ConsoleColor CSL_BG_LIGHT_CYAN = "\e[106m";
    inline const ConsoleColor CSL_BG_WHITE = "\e[107m";

}