/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

// LogicError, TypeError
#include "Core/Error.hpp"

// Variant
#include "Core/Variant.hpp"

oA::Variant::Variant(void) : _var(0.0f)
{
}

template<>
oA::Variant::Variant(const oA::Int &value) : _var(static_cast<oA::Float>(value))
{
}

oA::Variant &oA::Variant::operator=(const oA::Variant &other)
{
    _var = other._var;
    return *this;
}

template<>
oA::Variant &oA::Variant::operator=(const oA::Int &value)
{
    _var = static_cast<oA::Float>(value);
    return *this;
}

template<>
oA::Float &oA::Variant::get(void)
{
    assertType(VNumber);
    return std::get<Float>(_var);
}

template<>
oA::String &oA::Variant::get(void)
{
    assertType(VString);
    return std::get<String>(_var);
}

template<>
const oA::Float &oA::Variant::getConst(void) const
{
    assertType(VNumber);
    return std::get<Float>(_var);
}

template<>
const oA::String &oA::Variant::getConst(void) const
{
    assertType(VString);
    return std::get<String>(_var);
}

oA::Float oA::Variant::toFloat(void) const noexcept
{
    try {
        switch (index()) {
        case VNumber:
            return getConst<Float>();
        case VString:
            return std::stof(getConst<String>());
        default:
            return 0.0f;
        }
    } catch (const std::invalid_argument &) {
        return 0.0f;
    }
}

oA::Int oA::Variant::toInt(void) const noexcept
{
    try {
        switch (index()) {
        case VNumber:
            return static_cast<Int>(getConst<Float>());
        case VString:
            return std::stoi(getConst<String>());
        default:
            return 0;
        }
    } catch (const std::invalid_argument &) {
        return 0;
    }
}

oA::String oA::Variant::toString(void) const noexcept
{
    switch (index()) {
    case VNumber:
        return ToString(getConst<Float>());
    case VString:
        return getConst<String>();
    default:
        return String();
    }
}

oA::String oA::Variant::getTypeName(void) const noexcept
{
    return getTypeName(index());
}

oA::String oA::Variant::getTypeName(oA::VariantType type) const noexcept
{
    switch (type) {
    case VNumber:
        return "Number";
    case VString:
        return "String";
    default:
        return "None";
    }
}

oA::Variant::operator bool(void) const
{
    switch (index()) {
    case VNumber:
        return getConst<Float>();
    case VString:
        return !getConst<String>().empty();
    default:
        throw TypeError("Variant", "Invalid variant type for @operator b@ool");
    }
}

bool oA::Variant::operator==(const Variant &other) const
{
    if (!isSameType(other))
        return false;
    switch (index()) {
    case VNumber:
        return getConst<Float>() == other.getConst<Float>();
    case VString:
        return getConst<String>() == other.getConst<String>();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator ==@");
    }
}

bool oA::Variant::operator!=(const Variant &other) const
{
    return !(*this == other);
}

bool oA::Variant::operator<(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ < @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() < other.getConst<Float>();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator <@");
    }
}

bool oA::Variant::operator<=(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ <= @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() <= other.getConst<Float>();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator <=@");
    }
}

bool oA::Variant::operator>(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ > @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() > other.getConst<Float>();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator >@");
    }
}

bool oA::Variant::operator>=(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ >= @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() >= other.getConst<Float>();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator >=@");
    }
}


oA::Variant oA::Variant::operator+(const oA::Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ + @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() + other.getConst<Float>();
    case VString:
        return getConst<String>() + other.getConst<String>();
    default:
        throw LogicError("Variant", "@Operator +@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant &oA::Variant::operator+=(const oA::Variant &other)
{
    return (*this = *this + other);
}

oA::Variant &oA::Variant::operator++(void)
{
    switch (index()) {
    case VNumber:
        get<Float>()++;
        return (*this);
    default:
        throw LogicError("Variant", "@Operator ++@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant oA::Variant::operator-(const oA::Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ - @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() - other.getConst<Float>();
    default:
        throw LogicError("Variant", "@Operator -@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant &oA::Variant::operator-=(const oA::Variant &other)
{
    return (*this = *this - other);
}

oA::Variant &oA::Variant::operator--(void)
{
    switch (index()) {
    case VNumber:
        get<Float>()--;
        return (*this);
    default:
        throw LogicError("Variant", "@Operator --@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant oA::Variant::operator*(const oA::Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ * @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() * other.getConst<Float>();
    default:
        throw LogicError("Variant", "@Operator *@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant &oA::Variant::operator*=(const oA::Variant &other)
{
    return (*this = *this * other);
}

oA::Variant oA::Variant::operator/(const oA::Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ / @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() / other.getConst<Float>();
    default:
        throw LogicError("Variant", "@Operator /@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant &oA::Variant::operator/=(const oA::Variant &other)
{
    return (*this = *this / other);
}

oA::Variant oA::Variant::operator%(const oA::Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ % @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return toInt() % other.toInt();
    default:
        throw LogicError("Variant", "@Operator %@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Variant &oA::Variant::operator%=(const oA::Variant &other)
{
    return (*this = *this % other);
}

void oA::Variant::assertType(oA::VariantType type) const
{
    if (index() != type)
        throw AccessError("Variant", "Can't retreive @" + getTypeName(type) + "@ from @" + getTypeName() + "@");
}