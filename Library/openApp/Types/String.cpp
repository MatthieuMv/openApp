/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** String
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Types/String.hpp>

oA::String &oA::String::operator=(const String &other) noexcept
{
    this->assign(other);
    return *this;
}

oA::String &oA::String::operator=(String &&other) noexcept
{
    this->assign(std::move(other));
    return *this;
}

oA::String &oA::String::operator+=(const String &other) noexcept
{
    this->append(other);
    return *this;
}

oA::String &oA::String::operator+=(String &&other) noexcept
{
    this->append(std::move(other));
    return *this;
}

bool oA::String::toBool(void) const
{
    if (*this == "true")
        return true;
    else if (*this == "false")
        return false;
    throw CastError("String", "Can't convert @" + *this + "@ to Boolean");
}

oA::Int oA::String::toInt(void) const
{
    if (!isNumber())
        throw CastError("String", "Can't convert @" + *this + "@ to Int");
    return std::stoul(*this);
}

oA::UInt oA::String::toUInt(void) const
{
    if (!isNumber())
        throw CastError("String", "Can't convert @" + *this + "@ to UInt");
    return std::stoul(*this);
}

oA::Float oA::String::toFloat(void) const
{
    if (!isNumber())
        throw CastError("String", "Can't convert @" + *this + "@ to Float");
    return std::stof(*this);
}

oA::Double oA::String::toDouble(void) const
{
    if (!isNumber())
        throw CastError("String", "Can't convert @" + *this + "@ to Double");
    return std::stod(*this);
}

bool oA::String::isBoolean(void) const noexcept
{
    return *this == "true" || *this == "false";
}

bool oA::String::isNumber(void) const noexcept
{
    return isDecimal();
}

bool oA::String::isSigned(void) const noexcept
{
    auto it = begin();
    auto last = end();

    if (it == last)
        return false;
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

    if (it == last)
        return false;
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

void oA::String::replace(const String &from, const String &to)
{
    for (oA::ULong pos = this->find(from, 0); pos != this->npos; pos = this->find(from, pos)) {
        this->erase(pos, from.length());
        this->insert(pos, to);
    }
}

void oA::String::replaceWith(const String &from, const Function<String(void)> &to)
{
    for (oA::ULong pos = this->find(from, 0); pos != this->npos; pos = this->find(from, pos)) {
        this->erase(pos, from.length());
        this->insert(pos, to());
    }
}

bool oA::String::startWith(const String &other) const noexcept
{
    return !this->compare(0, other.length(), other);
}

bool oA::String::endWith(const String &other) const noexcept
{
    auto len = length(), olen = other.length();

    if (olen > len)
        return false;
    return !this->compare(len - olen, olen, other);
}

oA::String &oA::String::tryAppend(const String &other)
{
    if (!endWith(other))
        append(other);
    return *this;;
}