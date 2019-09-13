/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Color
*/

// std::regex
#include <regex>

#include <openApp/Types/Error.hpp>
#include <openApp/Types/Color.hpp>
#include <openApp/Containers/UMap.hpp>
#include <openApp/Containers/Vector.hpp>

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

static const std::regex RGBAMatch("[:digit:]+,[:digit:]+,[:digit:]+(,[:digit:]+)?", std::regex::optimize);

static oA::Color RetreiveColorArgs(const oA::String &color);

oA::Color oA::Color::RetreiveColor(const String &color)
{
    auto it = C_COLORS.find(color);

    if (it != C_COLORS.end())
        return it->second;
    if (!std::regex_match(color, RGBAMatch))
        return RetreiveColorArgs(color);
    throw LogicError("Color", "Invalid color @" + color + "@");
}

static oA::Color RetreiveColorArgs(const oA::String &color)
{
    oA::Vector<oA::UInt> vec;
    oA::String tmp;

    for (auto &c : color) {
        if (std::isdigit(c))
            tmp.push_back(c);
        else if (c == ',') {
            vec.push_back(tmp.toUInt());
            tmp.clear();
        }
    }
    vec.push_back(tmp.toUInt());
    if (vec.size() == 4)
        return oA::Color(vec[0], vec[1], vec[2], vec[3]);
    return oA::Color(vec[0], vec[1], vec[2]);
}

void oA::Color::set(UByte r, UByte g, UByte b, UByte a)
{
    _val = Pack(r, g, b, a);
}

void oA::Color::setTransparency(UByte a)
{
    _val = Pack(getR(), getG(), getB(), a);
}

oA::UInt oA::Color::Pack(UByte r, UByte g, UByte b, UByte a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}