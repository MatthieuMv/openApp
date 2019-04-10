/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Terminal
*/

#pragma once

#include "String.hpp"

using ConsoleColor = oA::String;

#define CSL_RESET ("\e[0m")

#define CSL_BOLD ("\e[1m")
#define CSL_DIM ("\e[2m")
#define CSL_UNDERLINED ("\e[4m")
#define CSL_BLINK ("\e[5m")
#define CSL_INVERTED ("\e[7m")
#define CSL_HIDDEN ("\e[8m")

#define CSL_DEFAULT ("\e[39m")
#define CSL_BLACK ("\e[30m")
#define CSL_RED ("\e[31m")
#define CSL_GREEN ("\e[32m")
#define CSL_YELLOW ("\e[33m")
#define CSL_BLUE ("\e[34m")
#define CSL_MAGENTA ("\e[35m")
#define CSL_CYAN ("\e[36m")
#define CSL_LIGHT_GRAY ("\e[37m")
#define CSL_DARK_GRAY ("\e[90m")
#define CSL_LIGHT_RED ("\e[91m")
#define CSL_LIGHT_GREEN ("\e[92m")
#define CSL_LIGHT_YELLOW ("\e[93m")
#define CSL_LIGHT_BLUE ("\e[94m")
#define CSL_LIGHT_MAGENTA ("\e[95m")
#define CSL_LIGHT_CYAN ("\e[96m")
#define CSL_WHITE ("\e[97m")

#define CSL_BG_DEFAULT ("\e[49m")
#define CSL_BG_BLACK ("\e[40m")
#define CSL_BG_RED ("\e[41m")
#define CSL_BG_GREEN ("\e[42m")
#define CSL_BG_YELLOW ("\e[43m")
#define CSL_BG_BLUE ("\e[44m")
#define CSL_BG_MAGENTA ("\e[45m")
#define CSL_BG_CYAN ("\e[46m")
#define CSL_BG_LIGHT_GRAY ("\e[47m")
#define CSL_BG_DARK_GRAY ("\e[100m")
#define CSL_BG_LIGHT_RED ("\e[101m")
#define CSL_BG_LIGHT_GREEN ("\e[102m")
#define CSL_BG_LIGHT_YELLOW ("\e[103m")
#define CSL_BG_LIGHT_BLUE ("\e[104m")
#define CSL_BG_LIGHT_MAGENTA ("\e[105m")
#define CSL_BG_LIGHT_CYAN ("\e[106m")
#define CSL_BG_WHITE ("\e[107m")