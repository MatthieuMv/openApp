/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Variant
*/

#include "App/Variant.hpp"

oA::Variant::Variant(void) : _var(0.0f) {}

template<> oA::Variant::Variant(const oA::Float &value) : _var(value) {}
template<> oA::Variant::Variant(const oA::Int &value) : _var(static_cast<oA::Float>(value)) {}
template<> oA::Variant::Variant(const oA::String &value) : _var(value) {}
template<> oA::Variant::Variant(const oA::ItemPtr &value) : _var(value) {}

oA::Variant::Variant(const oA::Variant &other) : _var(other._var) {}

oA::Float &oA::Variant::toFloat(void) { assertType(VNumber); return std::get<Float>(_var); }
oA::String &oA::Variant::toString(void) { assertType(VString); return std::get<String>(_var); }
oA::ItemPtr &oA::Variant::toItemPtr(void) { assertType(VItem); return std::get<ItemPtr>(_var); }

const oA::Float &oA::Variant::toFloat(void) const { assertType(VNumber); return std::get<Float>(_var); }
const oA::String &oA::Variant::toString(void) const { assertType(VString); return std::get<String>(_var); }
const oA::ItemPtr &oA::Variant::toItemPtr(void) const { assertType(VItem); return std::get<ItemPtr>(_var); }

oA::Int oA::Variant::toInt(void) const { return static_cast<Int>(toFloat()); }

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
    case VItem:
        return "Item";
    default:
        return "None";
    }
}

template<> oA::Variant &oA::Variant::operator=(const oA::Float &value) { _var = value; return *this; }
template<> oA::Variant &oA::Variant::operator=(const oA::Int &value) { _var = static_cast<oA::Float>(value); return *this; }
template<> oA::Variant &oA::Variant::operator=(const oA::String &value) { _var = value; return *this; }
template<> oA::Variant &oA::Variant::operator=(const oA::ItemPtr &value) { _var = value; return *this; }

oA::Variant::operator bool(void)
{
    switch (index()) {
    case VNumber:
        return toFloat();
    case VString:
        return !toString().empty();
    case VItem:
        return toItemPtr().operator bool();
    default:
        throw TypeError("Variant", "Invalid variant type for @operator b@ool");
    }
}

bool oA::Variant::operator==(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ == @" + other.getTypeName() + "=@");
    switch (index()) {
    case VNumber:
        return toFloat() == other.toFloat();
    case VString:
        return toString() == other.toString();
    case VItem:
        return toItemPtr().get() == other.toItemPtr().get();
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
        return toFloat() < other.toFloat();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator <@");
    }
}

bool oA::Variant::operator<=(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ <= @" + other.getTypeName() + "=@");
    switch (index()) {
    case VNumber:
        return toFloat() <= other.toFloat();
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
        return toFloat() > other.toFloat();
    default:
        throw LogicError("Variant", "Invalid variant type for @operator >@");
    }
}

bool oA::Variant::operator>=(const Variant &other) const
{
    if (!isSameType(other))
        throw LogicError("Variant", "Invalid operation @" + getTypeName() + "@ >= @" + other.getTypeName() + "=@");
    switch (index()) {
    case VNumber:
        return toFloat() >= other.toFloat();
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
        return toFloat() + other.toFloat();
    case VString:
        return toString() + other.toString();
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
        toFloat()++;
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
        return toFloat() - other.toFloat();
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
        toFloat()--;
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
        return toFloat() * other.toFloat();
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
        return toFloat() / other.toFloat();
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