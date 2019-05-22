/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** EventHandler
*/

// EventHandler
#include "EventHandler.hpp"

EventHandler::EventHandler(IrrlichtContext &context)
    : _context(context)
{
    context.device->setEventReceiver(this);
}

bool EventHandler::OnEvent(const irr::SEvent &event)
{
    oA::Event target;

    switch (event.EventType) {
    case irr::EET_MOUSE_INPUT_EVENT:
        target.initAsMouse();
        convertMouseEvent(target, event);
        break;
    case irr::EET_KEY_INPUT_EVENT:
        target.initAsKeyboard();
        convertKeyboardEvent(target, event);
        break;
    default:
        return false;
    }
    if (target.type() == oA::NullEvent)
        return false;
    _context.events.emplace(std::move(target));
    return true;
}

void EventHandler::convertMouseEvent(oA::Event &target, const irr::SEvent &event)
{
    auto &mouse = target.mouse();

    switch (event.MouseInput.Event) {
    case irr::EMIE_LMOUSE_PRESSED_DOWN:
        mouse.state = oA::MousePressed;
        mouse.key = oA::MouseLeft;
        break;
    case irr::EMIE_RMOUSE_PRESSED_DOWN:
        mouse.state = oA::MousePressed;
        mouse.key = oA::MouseRight;
        break;
    case irr::EMIE_MMOUSE_PRESSED_DOWN:
        mouse.state = oA::MousePressed;
        mouse.key = oA::MouseMiddle;
        break;
    case irr::EMIE_LMOUSE_LEFT_UP:
        mouse.state = oA::MouseReleased;
        mouse.key = oA::MouseLeft;
        break;
    case irr::EMIE_RMOUSE_LEFT_UP:
        mouse.state = oA::MouseReleased;
        mouse.key = oA::MouseRight;
        break;
    case irr::EMIE_MMOUSE_LEFT_UP:
        mouse.state = oA::MouseReleased;
        mouse.key = oA::MouseMiddle;
        break;
    case irr::EMIE_MOUSE_MOVED:
        mouse.state = oA::MouseMove;
        mouse.key = oA::MouseLeft;
        break;
    case irr::EMIE_MOUSE_WHEEL:
        mouse.state = oA::MouseWheel;
        mouse.key = oA::MouseMiddle;
        break;
    default:
        return;
    }
    target.setType(oA::Mouse);
    mouse.pos.x = event.MouseInput.X;
    mouse.pos.y = event.MouseInput.Y;
    mouse.shift = event.MouseInput.Shift;
    mouse.control = event.MouseInput.Control;
}

void EventHandler::convertKeyboardEvent(oA::Event &target, const irr::SEvent &event)
{
    auto key = convertKey(event.KeyInput.Key);
    auto &keyboard = target.keyboard();

    if (key == oA::KeyNull)
        return;
    target.setType(oA::Keyboard);
    keyboard.key = key;
    keyboard.shift = event.KeyInput.Shift;
    keyboard.control = event.KeyInput.Control;
    keyboard.state = event.KeyInput.PressedDown ? oA::KeyPressed : oA::KeyReleased;
}

oA::Key EventHandler::convertKey(irr::EKEY_CODE code) const noexcept
{
    static const oA::UMap<irr::EKEY_CODE, oA::Key> map {
        { irr::KEY_BACK,        oA::KeyBack },
        { irr::KEY_TAB,         oA::KeyTab },
        { irr::KEY_RETURN,      oA::KeyReturn },
        { irr::KEY_SHIFT,       oA::KeyShift },
        { irr::KEY_CONTROL,     oA::KeyControl },
        { irr::KEY_MENU,        oA::KeyAlt },
        { irr::KEY_CAPITAL,     oA::KeyCapital },
        { irr::KEY_ESCAPE,      oA::KeyEscape },
        { irr::KEY_SPACE,       oA::KeySpace },
        { irr::KEY_PRIOR,       oA::KeyPrior },
        { irr::KEY_NEXT,        oA::KeyNext },
        { irr::KEY_END,         oA::KeyEnd },
        { irr::KEY_HOME,        oA::KeyHome },
        { irr::KEY_LEFT,        oA::KeyLeft },
        { irr::KEY_UP,          oA::KeyUp },
        { irr::KEY_RIGHT,       oA::KeyRight },
        { irr::KEY_DOWN,        oA::KeyDown },
        { irr::KEY_DELETE,      oA::KeyDelete },
        { irr::KEY_KEY_0,       oA::Key0 },
        { irr::KEY_KEY_1,       oA::Key1 },
        { irr::KEY_KEY_2,       oA::Key2 },
        { irr::KEY_KEY_3,       oA::Key3 },
        { irr::KEY_KEY_4,       oA::Key4 },
        { irr::KEY_KEY_5,       oA::Key5 },
        { irr::KEY_KEY_6,       oA::Key6 },
        { irr::KEY_KEY_7,       oA::Key7 },
        { irr::KEY_KEY_8,       oA::Key8 },
        { irr::KEY_KEY_9,       oA::Key9 },
        { irr::KEY_KEY_A,       oA::KeyA },
        { irr::KEY_KEY_B,       oA::KeyB },
        { irr::KEY_KEY_C,       oA::KeyC },
        { irr::KEY_KEY_D,       oA::KeyD },
        { irr::KEY_KEY_E,       oA::KeyE },
        { irr::KEY_KEY_F,       oA::KeyF },
        { irr::KEY_KEY_G,       oA::KeyG },
        { irr::KEY_KEY_H,       oA::KeyH },
        { irr::KEY_KEY_I,       oA::KeyI },
        { irr::KEY_KEY_J,       oA::KeyJ },
        { irr::KEY_KEY_K,       oA::KeyK },
        { irr::KEY_KEY_L,       oA::KeyL },
        { irr::KEY_KEY_M,       oA::KeyM },
        { irr::KEY_KEY_N,       oA::KeyN },
        { irr::KEY_KEY_O,       oA::KeyO },
        { irr::KEY_KEY_P,       oA::KeyP },
        { irr::KEY_KEY_Q,       oA::KeyQ },
        { irr::KEY_KEY_R,       oA::KeyR },
        { irr::KEY_KEY_S,       oA::KeyS },
        { irr::KEY_KEY_T,       oA::KeyT },
        { irr::KEY_KEY_U,       oA::KeyU },
        { irr::KEY_KEY_V,       oA::KeyV },
        { irr::KEY_KEY_W,       oA::KeyW },
        { irr::KEY_KEY_X,       oA::KeyX },
        { irr::KEY_KEY_Y,       oA::KeyY },
        { irr::KEY_KEY_Z,       oA::KeyZ },
        { irr::KEY_NUMPAD0,     oA::KeyNumpad0 },
        { irr::KEY_NUMPAD1,     oA::KeyNumpad1 },
        { irr::KEY_NUMPAD2,     oA::KeyNumpad2 },
        { irr::KEY_NUMPAD3,     oA::KeyNumpad3 },
        { irr::KEY_NUMPAD4,     oA::KeyNumpad4 },
        { irr::KEY_NUMPAD5,     oA::KeyNumpad5 },
        { irr::KEY_NUMPAD6,     oA::KeyNumpad6 },
        { irr::KEY_NUMPAD7,     oA::KeyNumpad7 },
        { irr::KEY_NUMPAD8,     oA::KeyNumpad8 },
        { irr::KEY_NUMPAD9,     oA::KeyNumpad9 },
        { irr::KEY_MULTIPLY,    oA::KeyMultiply },
        { irr::KEY_ADD,         oA::KeyAdd },
        { irr::KEY_SEPARATOR,   oA::KeySeparator },
        { irr::KEY_SUBTRACT,    oA::KeySubtract },
        { irr::KEY_DECIMAL,     oA::KeyDecimal },
        { irr::KEY_DIVIDE,      oA::KeyDivide },
        { irr::KEY_F1,          oA::KeyF1 },
        { irr::KEY_F2,          oA::KeyF2 },
        { irr::KEY_F3,          oA::KeyF3 },
        { irr::KEY_F4,          oA::KeyF4 },
        { irr::KEY_F5,          oA::KeyF5 },
        { irr::KEY_F6,          oA::KeyF6 },
        { irr::KEY_F7,          oA::KeyF7 },
        { irr::KEY_F8,          oA::KeyF8 },
        { irr::KEY_F9,          oA::KeyF9 },
        { irr::KEY_F10,         oA::KeyF10 },
        { irr::KEY_F11,         oA::KeyF11 },
        { irr::KEY_F12,         oA::KeyF12 },
        { irr::KEY_F13,         oA::KeyF13 },
        { irr::KEY_F14,         oA::KeyF14 },
        { irr::KEY_F15,         oA::KeyF15 },
        { irr::KEY_F16,         oA::KeyF16 },
        { irr::KEY_F17,         oA::KeyF17 },
        { irr::KEY_F18,         oA::KeyF18 },
        { irr::KEY_F19,         oA::KeyF19 },
        { irr::KEY_F20,         oA::KeyF20 },
        { irr::KEY_F21,         oA::KeyF21 },
        { irr::KEY_F22,         oA::KeyF22 },
        { irr::KEY_F23,         oA::KeyF23 },
        { irr::KEY_F24,         oA::KeyF24 },
        { irr::KEY_NUMLOCK,     oA::KeyNumlock },
        { irr::KEY_SCROLL,      oA::KeyScroll },
        { irr::KEY_LSHIFT,      oA::KeyLshift },
        { irr::KEY_RSHIFT,      oA::KeyRshift },
        { irr::KEY_LCONTROL,    oA::KeyLcontrol },
        { irr::KEY_RCONTROL,    oA::KeyRcontrol },
        { irr::KEY_OEM_1,       oA::KeyOem_1 },
        { irr::KEY_PLUS,        oA::KeyPlus },
        { irr::KEY_COMMA,       oA::KeyComma },
        { irr::KEY_MINUS,       oA::KeyMinus },
        { irr::KEY_PERIOD,      oA::KeyPeriod },
        { irr::KEY_OEM_2,       oA::KeyOem_2 },
        { irr::KEY_OEM_3,       oA::KeyOem_3 },
        { irr::KEY_OEM_4,       oA::KeyOem_4 },
        { irr::KEY_OEM_5,       oA::KeyOem_5 },
        { irr::KEY_OEM_6,       oA::KeyOem_6 },
        { irr::KEY_OEM_7,       oA::KeyOem_7 },
        { irr::KEY_OEM_102,     oA::KeyOem_102 }
    };
    auto it = map.find(code);

    if (it == map.end())
        return oA::KeyNull;
    return it->second;
}