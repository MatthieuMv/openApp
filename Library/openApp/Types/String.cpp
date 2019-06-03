/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** String
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Types/String.hpp>

bool oA::String::toBool(void) const
{
    if (*this == "true")
        return true;
    else if (*this == "false")
        return false;
    throw oA::CastError("String", "Can't convert @" + *this + "@ to Boolean");
}

oA::Int oA::String::toInt(void) const
{
    if (!isSigned())
        throw oA::CastError("String", "Can't convert @" + *this + "@ to Int");
    return std::stoi(*this);
}

oA::Uint oA::String::toUint(void) const
{
    if (!isUnsigned())
        throw oA::CastError("String", "Can't convert @" + *this + "@ to Uint");
    return std::stoul(*this);
}

oA::Float oA::String::toFloat(void) const
{
    if (!isDecimal())
        throw oA::CastError("String", "Can't convert @" + *this + "@ to Float");
    return std::stof(*this);
}

oA::Double oA::String::toDouble(void) const
{
    if (!isDecimal())
        throw oA::CastError("String", "Can't convert @" + *this + "@ to Double");
    return std::stod(*this);
}

bool oA::String::isBoolean(void) const noexcept
{
    return *this == "true" || *this == "false";
}

bool oA::String::isSigned(void) const noexcept
{
    auto it = begin();
    auto last = end();

    if (*it == '-')
        ++it;
    for (; it != last; ++it) {
        if (!std::isdigit(*it))
            return false;
    }
    return true;
}

bool oA::String::isUnsigned(void) const noexcept
{
    for (auto c : *this) {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

bool oA::String::isDecimal(void) const noexcept
{
    auto it = begin();
    auto last = end();
    bool hasSeparator = false;

    if (*it == '-')
        ++it;
    for (; it != last; ++it) {
        if (*it == '.') {
            if (hasSeparator)
                return false;
            hasSeparator = true;
            continue;
        }
        if (!std::isdigit(*it))
            return false;
    }
    return true;
}
