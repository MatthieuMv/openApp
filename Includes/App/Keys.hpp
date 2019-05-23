/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Keys
*/

#pragma once

namespace oA
{
    enum MouseState {
        MousePressed = 0,
        MouseReleased,
        MouseWheel,
        MouseMove
    };

    enum MouseKey {
        MouseNull = 0,      // Null
        MouseLeft,          // Left mouse button
        MouseRight,         // Right mouse button
        MouseMiddle,        // Middle mouse button (three-button mouse)
    };

    enum KeyState {
        KeyPressed = 0,
        KeyReleased
    };

    enum Key {
        KeyNull = 0,    // Null
        KeyBack,        // BACKSPACE key
        KeyTab,         // TAB key
        KeyReturn,      // ENTER key
        KeyShift,       // SHIFT key
        KeyControl,     // CTRL key
        KeyAlt,         // ALT key
        KeyCapital,     // CAPS LOCK key
        KeyEscape,      // ESC key
        KeySpace,       // SPACEBAR
        KeyPrior,       // PAGE UP key
        KeyNext,        // PAGE DOWN key
        KeyEnd,         // END key
        KeyHome,        // HOME key
        KeyLeft,        // LEFT ARROW key
        KeyUp,          // UP ARROW key
        KeyRight,       // RIGHT ARROW key
        KeyDown,        // DOWN ARROW key
        KeyDelete,      // DEL key
        Key0,           // 0 key
        Key1,           // 1 key
        Key2,           // 2 key
        Key3,           // 3 key
        Key4,           // 4 key
        Key5,           // 5 key
        Key6,           // 6 key
        Key7,           // 7 key
        Key8,           // 8 key
        Key9,           // 9 key
        KeyA,           // A key
        KeyB,           // B key
        KeyC,           // C key
        KeyD,           // D key
        KeyE,           // E key
        KeyF,           // F key
        KeyG,           // G key
        KeyH,           // H key
        KeyI,           // I key
        KeyJ,           // J key
        KeyK,           // K key
        KeyL,           // L key
        KeyM,           // M key
        KeyN,           // N key
        KeyO,           // O key
        KeyP,           // P key
        KeyQ,           // Q key
        KeyR,           // R key
        KeyS,           // S key
        KeyT,           // T key
        KeyU,           // U key
        KeyV,           // V key
        KeyW,           // W key
        KeyX,           // X key
        KeyY,           // Y key
        KeyZ,           // Z key
        KeyNumpad0,     // Numeric keypad 0 key
        KeyNumpad1,     // Numeric keypad 1 key
        KeyNumpad2,     // Numeric keypad 2 key
        KeyNumpad3,     // Numeric keypad 3 key
        KeyNumpad4,     // Numeric keypad 4 key
        KeyNumpad5,     // Numeric keypad 5 key
        KeyNumpad6,     // Numeric keypad 6 key
        KeyNumpad7,     // Numeric keypad 7 key
        KeyNumpad8,     // Numeric keypad 8 key
        KeyNumpad9,     // Numeric keypad 9 key
        KeyMultiply,    // Multiply key
        KeyAdd,         // Addition key
        KeySeparator,   // Separator key
        KeySubtract,    // Subtract key
        KeyDecimal,     // Decimal key
        KeyDivide,      // Divide key
        KeyF1,          // F1 key
        KeyF2,          // F2 key
        KeyF3,          // F3 key
        KeyF4,          // F4 key
        KeyF5,          // F5 key
        KeyF6,          // F6 key
        KeyF7,          // F7 key
        KeyF8,          // F8 key
        KeyF9,          // F9 key
        KeyF10,         // F10 key
        KeyF11,         // F11 key
        KeyF12,         // F12 key
        KeyF13,         // F13 key
        KeyF14,         // F14 key
        KeyF15,         // F15 key
        KeyF16,         // F16 key
        KeyF17,         // F17 key
        KeyF18,         // F18 key
        KeyF19,         // F19 key
        KeyF20,         // F20 key
        KeyF21,         // F21 key
        KeyF22,         // F22 key
        KeyF23,         // F23 key
        KeyF24,         // F24 key
        KeyNumlock,     // NUM LOCK key
        KeyScroll,      // SCROLL LOCK key
        KeyLshift,      // Left SHIFT key
        KeyRshift,      // Right SHIFT key
        KeyLcontrol,    // Left CONTROL key
        KeyRcontrol,    // Right CONTROL key
        KeyOem_1,       // for US    ";:"
        KeyPlus,        // Plus Key   "+"
        KeyComma,       // Comma Key  ","
        KeyMinus,       // Minus Key  "-"
        KeyPeriod,      // Period Key "."
        KeyOem_2,       // for US    "/?"
        KeyOem_3,       // for US    "`~"
        KeyOem_4,       // for US    "[{"
        KeyOem_5,       // for US    "\|"
        KeyOem_6,       // for US    "]}"
        KeyOem_7,       // for US    "'""
        KeyOem_102,     // "<>" or "\|"
        KeyTotal
    };
}