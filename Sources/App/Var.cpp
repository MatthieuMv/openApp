/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Var
*/

// LogicError, TypeError
#include "Core/Error.hpp"

// Var
#include "App/Var.hpp"

oA::Var::Var(void) : _var(0.0f) {}

oA::Var &oA::Var::operator=(const Var &other)
{
    _var = other._var;
    return *this;
}

template<>
oA::Var &oA::Var::operator=(const Int &value)
{
    _var = static_cast<Float>(value);
    return *this;
}

template<>
oA::Float &oA::Var::get(void)
{
    assertType(VNumber);
    return oA::Get<Float>(_var);
}

template<>
oA::String &oA::Var::get(void)
{
    assertType(VString);
    return oA::Get<String>(_var);
}

template<>
const oA::Float &oA::Var::getConst(void) const
{
    assertType(VNumber);
    return oA::Get<Float>(_var);
}

template<>
const oA::String &oA::Var::getConst(void) const
{
    assertType(VString);
    return oA::Get<String>(_var);
}

oA::Float oA::Var::toFloat(void) const noexcept
{
    try {
        switch (index()) {
        case VNumber:
            return getConst<Float>();
        case VString:
            return std::stof(getConst<String>());
        }
    } catch (const std::invalid_argument &) {}
    return 0.0f;
}

oA::Int oA::Var::toInt(void) const noexcept
{
    try {
        switch (index()) {
        case VNumber:
            return static_cast<Int>(getConst<Float>());
        case VString:
            return std::stoi(getConst<String>());
        }
    } catch (const std::invalid_argument &) {}
    return 0;
}

oA::String oA::Var::toString(void) const noexcept
{
    switch (index()) {
    case VNumber:
        return ToString(getConst<Float>());
    case VString:
        return getConst<String>();
    }
    return String();
}

oA::String oA::Var::getTypeName(void) const noexcept
{
    return getTypeName(index());
}

oA::String oA::Var::getTypeName(oA::VarType type) const noexcept
{
    switch (type) {
    case VNumber:
        return "Number";
    case VString:
        return "String";
    }
    return "None";
}

oA::Var::operator bool(void) const
{
    switch (index()) {
    case VNumber:
        return getConst<Float>();
    case VString:
        return !getConst<String>().empty();
    }
    return false;
}

bool oA::Var::operator==(const Var &other) const
{
    if (!isSameType(other))
        return toString() == other.toString();
    switch (index()) {
    case VNumber:
        return getConst<Float>() == other.getConst<Float>();
    case VString:
        return getConst<String>() == other.getConst<String>();
    }
    return false;
}

bool oA::Var::operator!=(const Var &other) const
{
    return !(*this == other);
}

bool oA::Var::operator<(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ < @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() < other.getConst<Float>();
    default:
        throw LogicError("Var", "Invalid variant type for @operator <@");
    }
}

bool oA::Var::operator<=(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ <= @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() <= other.getConst<Float>();
    default:
        throw LogicError("Var", "Invalid variant type for @operator <=@");
    }
}

bool oA::Var::operator>(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ > @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() > other.getConst<Float>();
    default:
        throw LogicError("Var", "Invalid variant type for @operator >@");
    }
}

bool oA::Var::operator>=(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ >= @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() >= other.getConst<Float>();
    default:
        throw LogicError("Var", "Invalid variant type for @operator >=@");
    }
}


oA::Var oA::Var::operator+(const Var &other) const
{
    if (!isSameType(other))
        return toString() + other.toString();
    switch (index()) {
    case VNumber:
        return getConst<Float>() + other.getConst<Float>();
    case VString:
        return getConst<String>() + other.getConst<String>();
    }
    return Var();
}

oA::Var &oA::Var::operator+=(const Var &other)
{
    return (*this = *this + other);
}

oA::Var &oA::Var::operator++(void)
{
    switch (index()) {
    case VNumber:
        ++get<Float>();
        return (*this);
    default:
        throw LogicError("Var", "@Operator ++@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var oA::Var::operator++(int)
{
    switch (index()) {
    case VNumber:
        ++get<Float>();
        return (*this);
    default:
        throw LogicError("Var", "@Operator ++@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var oA::Var::operator-(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ - @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() - other.getConst<Float>();
    default:
        throw LogicError("Var", "@Operator -@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var &oA::Var::operator-=(const Var &other)
{
    return (*this = *this - other);
}

oA::Var &oA::Var::operator--(void)
{
    switch (index()) {
    case VNumber:
        get<Float>()--;
        return (*this);
    default:
        throw LogicError("Var", "@Operator --@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var oA::Var::operator--(int)
{
    switch (index()) {
    case VNumber:
        --get<Float>();
        return (*this);
    default:
        throw LogicError("Var", "@Operator --@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var oA::Var::operator*(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ * @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() * other.getConst<Float>();
    default:
        throw LogicError("Var", "@Operator *@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var &oA::Var::operator*=(const Var &other)
{
    return (*this = *this * other);
}

oA::Var oA::Var::operator/(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ / @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return getConst<Float>() / other.getConst<Float>();
    default:
        throw LogicError("Var", "@Operator /@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var &oA::Var::operator/=(const Var &other)
{
    return (*this = *this / other);
}

oA::Var oA::Var::operator%(const Var &other) const
{
    if (!isSameType(other))
        throw LogicError("Var", "Invalid operation @" + getTypeName() + "@ % @" + other.getTypeName() + "@");
    switch (index()) {
    case VNumber:
        return toInt() % other.toInt();
    default:
        throw LogicError("Var", "@Operator %@ not implemented for @" + getTypeName() + "@");
    }
}

oA::Var &oA::Var::operator%=(const Var &other)
{
    return (*this = *this % other);
}

void oA::Var::assertType(VarType type) const
{
    if (index() != type)
        throw AccessError("Var", "Can't retreive @" + getTypeName(type) + "@ from @" + getTypeName() + "@");
}

oA::Log &operator<<(oA::Log &log, const oA::Var &var)
{
    log.log(var.toString());
    return (log);
}