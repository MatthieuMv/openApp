/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Color
*/

#include <openApp/Types/Color.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>

static const oA::UMap<oA::String, oA::Color> C_COLORS = {
    { "transparent",    oA::Color(0, 0, 0, 0)       },
    { "black",          oA::Color(0, 0, 0)          },
    { "white",          oA::Color(255, 255, 255)    },
    { "grey",           oA::Color(125, 125, 125)    },
    { "lightgrey",      oA::Color(200, 200, 200)    },
    { "darkgrey",       oA::Color(75, 75, 75)       },
    { "red",            oA::Color(255, 0, 0)        },
    { "lightred",       oA::Color(255, 75, 75)      },
    { "darkred",        oA::Color(125, 0, 0)        },
    { "green",          oA::Color(0, 255, 0)        },
    { "lightgreen",     oA::Color(75, 255, 75)      },
    { "darkgreen",      oA::Color(0, 125, 0)        },
    { "blue",           oA::Color(0, 0, 255)        },
    { "lightblue",      oA::Color(75, 75, 255)      },
    { "darkblue",       oA::Color(0, 0, 125)        },
    { "cyan",           oA::Color(0, 255, 255)      },
    { "lightcyan",      oA::Color(100, 255, 255)    },
    { "darkcyan",       oA::Color(0, 125, 125)      },
    { "magenta",        oA::Color(255, 0, 255)      },
    { "lightmagenta",   oA::Color(255, 100, 255)    },
    { "darkmagenta",    oA::Color(125, 0, 125)      },
    { "yellow",         oA::Color(255, 255, 0)      },
    { "lightyellow",    oA::Color(255, 255, 100)    },
    { "darkyellow",     oA::Color(125, 125, 0)      },
    { "lightorange",    oA::Color(255, 195, 0)      },
    { "orange",         oA::Color(255, 165, 0)      },
    { "darkorange",     oA::Color(255, 140, 0)      }
};

oA::Color oA::Color::RetreiveColor(const String &color)
{
    auto it = C_COLORS.find(color);

    if (it == C_COLORS.end())
        throw LogicError("Color", "Invalid color name @" + color + "@");
    return it->second;
}

void oA::Color::set(UByte r, UByte g, UByte b, UByte a)
{
    _val = Pack(r, g, b, a);
}

void oA::Color::setTransparency(UByte a)
{
    _val = Pack(getR(), getG(), getB(), a);
}

oA::Uint oA::Color::Pack(UByte r, UByte g, UByte b, UByte a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}