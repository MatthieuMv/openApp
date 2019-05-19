/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Event
*/

// Map
#include "Core/Map.hpp"
// Event
#include "App/Event.hpp"

static char shiftChar(char c);

static const oA::Map<oA::Key, char> C_KEYS = {
        { oA::KeyTab,           '\t'    },  // TAB key
        { oA::KeySpace,         ' '     },  // SPACEBAR
        { oA::Key0,             '0'     },  // 0 key
        { oA::Key1,             '1'     },  // 1 key
        { oA::Key2,             '2'     },  // 2 key
        { oA::Key3,             '3'     },  // 3 key
        { oA::Key4,             '4'     },  // 4 key
        { oA::Key5,             '5'     },  // 5 key
        { oA::Key6,             '6'     },  // 6 key
        { oA::Key7,             '7'     },  // 7 key
        { oA::Key8,             '8'     },  // 8 key
        { oA::Key9,             '9'     },  // 9 key
        { oA::KeyA,             'a'     },  // A key
        { oA::KeyB,             'b'     },  // B key
        { oA::KeyC,             'c'     },  // C key
        { oA::KeyD,             'd'     },  // D key
        { oA::KeyE,             'e'     },  // E key
        { oA::KeyF,             'f'     },  // F key
        { oA::KeyG,             'g'     },  // G key
        { oA::KeyH,             'h'     },  // H key
        { oA::KeyI,             'i'     },  // I key
        { oA::KeyJ,             'j'     },  // J key
        { oA::KeyK,             'k'     },  // K key
        { oA::KeyL,             'l'     },  // L key
        { oA::KeyM,             'm'     },  // M key
        { oA::KeyN,             'n'     },  // N key
        { oA::KeyO,             'o'     },  // O key
        { oA::KeyP,             'p'     },  // P key
        { oA::KeyQ,             'q'     },  // Q key
        { oA::KeyR,             'r'     },  // R key
        { oA::KeyS,             's'     },  // S key
        { oA::KeyT,             't'     },  // T key
        { oA::KeyU,             'u'     },  // U key
        { oA::KeyV,             'v'     },  // V key
        { oA::KeyW,             'w'     },  // W key
        { oA::KeyX,             'x'     },  // X key
        { oA::KeyY,             'y'     },  // Y key
        { oA::KeyZ,             'z'     },  // Z key
        { oA::KeyNumpad0,       '0'     },  // Numeric keypad 0 key
        { oA::KeyNumpad1,       '1'     },  // Numeric keypad 1 key
        { oA::KeyNumpad2,       '2'     },  // Numeric keypad 2 key
        { oA::KeyNumpad3,       '3'     },  // Numeric keypad 3 key
        { oA::KeyNumpad4,       '4'     },  // Numeric keypad 4 key
        { oA::KeyNumpad5,       '5'     },  // Numeric keypad 5 key
        { oA::KeyNumpad6,       '6'     },  // Numeric keypad 6 key
        { oA::KeyNumpad7,       '7'     },  // Numeric keypad 7 key
        { oA::KeyNumpad8,       '8'     },  // Numeric keypad 8 key
        { oA::KeyNumpad9,       '9'     },  // Numeric keypad 9 key
        { oA::KeyMultiply,      '*'     },  // Multiply key
        { oA::KeyAdd,           '+'     },  // Add key
        { oA::KeySeparator,     '\n'    },  // Separator key
        { oA::KeySubtract,      '-'     },  // Subtract key
        { oA::KeyDecimal,       '.'     },  // Decimal key
        { oA::KeyDivide,        '/'     },  // Divide key
        { oA::KeyOem_1,         ';'     },  // for US    ";:"
        { oA::KeyPlus,          '+'     },  // Plus Key   "+"
        { oA::KeyComma,         ','     },  // Comma Key  ","
        { oA::KeyMinus,         '-'     },  // Minus Key  "-"
        { oA::KeyPeriod,        '.'     },  // Period Key "."
        { oA::KeyOem_2,         '/'     },  // for US    "/?"
        { oA::KeyOem_3,         '`'     },  // for US    "`~"
        { oA::KeyOem_4,         '['     },  // for US    "[{"
        { oA::KeyOem_5,         '\\'    },  // for US    "\|"
        { oA::KeyOem_6,         ']'     },  // for US    "]}"
        { oA::KeyOem_7,         '\''    },  // for US    "'""
        { oA::KeyOem_102,       '<'     }  // "<>" or "\|"
};

char oA::KeyboardEvent::convetToKey(void) const noexcept
{
    auto it = C_KEYS.find(key);

    if (it == C_KEYS.end())
        return '\0';
    if (shift)
        return shiftChar(it->second);
    return it->second;
}

static char shiftChar(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    switch (c) {
    case ';':
        return ':';
    case '/':
        return '?';
    case '`':
        return '~';
    case '[':
        return '{';
    case ']':
        return '}';
    case '\'':
        return '"';
    case '<':
        return '>';
    default:
        return c;
    }
}