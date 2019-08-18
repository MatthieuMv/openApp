/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Var
*/

#include <openApp/Types/Error.hpp>
#include <openApp/Core/Var.hpp>

void oA::Var::swap(Var &other) noexcept
{
    Signal<>::swap(other);
    _var = std::move(other._var);
}

bool oA::Var::toBool(void) const noexcept
{
    return operator bool();
}

oA::Int oA::Var::toInt(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) {
            return static_cast<Int>(number);
        },
        [] (const Literal &literal) {
            if (literal.isNumber())
                return literal.toInt();
            return 0;
        },
        [] (const Container &) {
            return 0;
        }
    }, _var);
}

oA::Uint oA::Var::toUint(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) -> Uint {
            return static_cast<Uint>(number);
        },
        [] (const Literal &literal) -> Uint {
            if (literal.isNumber())
                return literal.toUint();
            return 0;
        },
        [] (const Container &) -> Uint {
            return 0;
        }
    }, _var);
}

oA::Float oA::Var::toFloat(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) {
            return number;
        },
        [] (const Literal &literal) {
            if (literal.isNumber())
                return literal.toFloat();
            return 0.0f;
        },
        [] (const Container &) {
            return 0.0f;
        }
    }, _var);
}

oA::String oA::Var::toString(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) {
            return ToString(number);
        },
        [] (const Literal &literal) {
            return literal;
        },
        [] (const Container &) {
            return String();
        }
    }, _var);
}

oA::Var &oA::Var::operator=(const Var &other)
{
    if (_var != other._var) {
        _var = other._var;
        this->emit();
    }
    return *this;
}

oA::Var &oA::Var::operator=(Var &&other)
{
    if (_var != other._var) {
        _var = std::move(other._var);
        this->emit();
    }
    return *this;
}

oA::Var::operator bool(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) {
            return number ? true : false;
        },
        [] (const Literal &literal) {
            return !literal.empty();
        },
        [] (const Container &container) {
            return !container.empty();
        }
    }, _var);
}

bool oA::Var::operator!(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) {
            return !number ? true : false;
        },
        [] (const Literal &literal) {
            return literal.empty();
        },
        [] (const Container &container) {
            return container.empty();
        }
    }, _var);
}

bool oA::Var::operator==(const Var &other) const
{
    return _var == other._var;
}

bool oA::Var::operator!=(const Var &other) const
{
    return !(*this == other);
}

bool oA::Var::operator<(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) {
            return number < other.toFloat();
        },
        [] (const Literal &) -> bool {
            throw LogicError("Var", "Can't use operator < on @Literal@");
        },
        [] (const Container &) -> bool {
            throw LogicError("Var", "Can't use operator < on @Container@");
        }
    }, _var);
}

bool oA::Var::operator<=(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) {
            return number <= other.toFloat();
        },
        [] (const Literal &) -> bool {
            throw LogicError("Var", "Can't use operator <= on @Literal@");
        },
        [] (const Container &) -> bool {
            throw LogicError("Var", "Can't use operator <= on @Container@");
        }
    }, _var);
}

bool oA::Var::operator>(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) {
            return number > other.toFloat();
        },
        [] (const Literal &) -> bool {
            throw LogicError("Var", "Can't use operator > on @Literal@");
        },
        [] (const Container &) -> bool {
            throw LogicError("Var", "Can't use operator > on @Container@");
        }
    }, _var);
}

bool oA::Var::operator>=(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) {
            return number >= other.toFloat();
        },
        [] (const Literal &) -> bool {
            throw LogicError("Var", "Can't use operator >= on @Literal@");
        },
        [] (const Container &) -> bool {
            throw LogicError("Var", "Can't use operator >= on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator+(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> Var {
            return number + other.toFloat();
        },
        [&other] (const Literal &literal) -> Var {
            return literal + other.toString();
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator + on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator-(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> Var {
            return number - other.toFloat();
        },
        [] (const Literal &) -> Var {
            throw LogicError("Var", "Can't use operator - on @Literal@");
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator - on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator*(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> Var {
            return number * other.toFloat();
        },
        [] (const Literal &) -> Var {
            throw LogicError("Var", "Can't use operator * on @Literal@");
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator * on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator/(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> Var {
            return number / other.toFloat();
        },
        [] (const Literal &) -> Var {
            throw LogicError("Var", "Can't use operator / on @Literal@");
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator / on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator%(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> Var {
            return static_cast<Int>(number) % other.toInt();
        },
        [] (const Literal &) -> Var {
            throw LogicError("Var", "Can't use operator % on @Literal@");
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator % on @Container@");
        }
    }, _var);
}

oA::Var &oA::Var::operator+=(const Var &other)
{
    if (std::visit(Overload {
        [&other] (Number &number) -> bool {
            auto x = number;
            number += other.toFloat();
            return x != number;
        },
        [&other] (Literal &literal) -> bool {
            auto str = other.toString();
            literal += str;
            return !str.empty();
        },
        [this, &other] (Container &container) -> bool {
            container.push_back(other);
            container.back().connect([this]{ this->emit(); return true; });
            return true;
        }
        }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::operator-=(const Var &other)
{
    if (std::visit(Overload {
        [&other] (Number &number) -> bool {
            auto x = number;
            number -= other.toFloat();
            return x != number;
        },
        [] (Literal &) -> bool {
            throw LogicError("Var", "Can't use operator -= on @Literal@");
        },
        [&other] (Container &container) -> bool {
            auto it = container.begin();
            auto idx = other.toUint();
            if (other.index() != VNumber)
                throw LogicError("Var", "Operator -= on @Container@ must be used with a Number");
            if (container.size() <= idx)
                throw AccessError("Var," "Operator -= on @Container@ used with out of range index @" + ToString(idx) + "@");
            std::advance(it, idx);
            container.erase(it);
            return true;
        }
    }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::operator*=(const Var &other)
{
    if (std::visit(Overload {
        [&other] (Number &number) -> bool {
            auto x = number;
            number *= other.toFloat();
            return x != number;
        },
        [] (Literal &) -> bool {
            throw LogicError("Var", "Can't use operator *= on @Literal@");
        },
        [] (Container &) -> bool {
            throw LogicError("Var", "Can't use operator *= on @Container@");
        }
    }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::operator/=(const Var &other)
{
    if (std::visit(Overload {
        [&other] (Number &number) -> bool {
            auto x = number, y = other.toFloat();
            if (!y)
                throw LogicError("Var", "Can't divide number by 0");
            number /= y;
            return x != number;
        },
        [] (Literal &) -> bool {
            throw LogicError("Var", "Can't use operator /= on @Literal@");
        },
        [] (Container &) -> bool {
            throw LogicError("Var", "Can't use operator /= on @Container@");
        }
    }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::operator%=(const Var &other)
{
    if (std::visit(Overload {
        [&other] (Number &number) -> bool {
            auto x = number, y = other.toFloat();
            if (!y)
                throw LogicError("Var", "Can't mod number by 0");
            number = static_cast<Int>(number) % static_cast<Int>(y);
            return x != number;
        },
        [] (Literal &) -> bool {
            throw LogicError("Var", "Can't use operator %= on @Literal@");
        },
        [] (Container &) -> bool {
            throw LogicError("Var", "Can't use operator %= on @Container@");
        }
    }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::operator++(void)
{
    std::visit(Overload {
        [] (Number &number) {
            ++number;
        },
        [] (Literal &) {
            throw LogicError("Var", "Can't use operator ++ on @Literal@");
        },
        [] (Container &) {
            throw LogicError("Var", "Can't use operator ++ on @Container@");
        }
    }, _var);
    this->emit();
    return *this;
}

oA::Var &oA::Var::operator--(void)
{
    std::visit(Overload {
        [] (Number &number) {
            --number;
        },
        [] (Literal &) {
            throw LogicError("Var", "Can't use operator -- on @Literal@");
        },
        [] (Container &) {
            throw LogicError("Var", "Can't use operator -- on @Container@");
        }
    }, _var);
    this->emit();
    return *this;
}

oA::Var oA::Var::operator++(oA::Int)
{
    auto res = std::visit(Overload {
        [] (Number &number) -> Var {
            return number++;
        },
        [] (Literal &) -> Var {
            throw LogicError("Var", "Can't use operator ++ on @Literal@");
        },
        [] (Container &) -> Var {
            throw LogicError("Var", "Can't use operator ++ on @Container@");
        }
    }, _var);
    this->emit();
    return res;
}

oA::Var oA::Var::operator--(oA::Int)
{
    auto res = std::visit(Overload {
        [] (Number &number) -> Var {
            return number--;
        },
        [] (Literal &) -> Var {
            throw LogicError("Var", "Can't use operator -- on @Literal@");
        },
        [] (Container &) -> Var {
            throw LogicError("Var", "Can't use operator -- on @Container@");
        }
    }, _var);
    this->emit();
    return res;
}

oA::Var &oA::Var::operator[](const Var &other)
{
    return std::visit(Overload {
        [] (Number &) -> Var& {
            throw LogicError("Var", "Can't use operator [] on @Number@");
        },
        [] (Literal &) -> Var& {
            throw LogicError("Var", "Can't use operator [] on @Literal@");
        },
        [this, &other] (Container &container) -> Var& {
            auto it = container.begin();
            auto idx = other.toUint();
            if (other.index() != VNumber)
                throw LogicError("Var", "Operator [] on @Container@ must be used with a Number");
            if (container.size() <= idx)
                throw AccessError("Var," "Operator [] on @Container@ used with out of range index @" + ToString(idx) + "@");
            std::advance(it, idx);
            this->emit();
            return *it;
        }
    }, _var);
}

const oA::Var &oA::Var::operator[](const Var &other) const
{
    return std::visit(Overload {
        [] (const Number &) -> const Var& {
            throw LogicError("Var", "Can't use operator [] on @Number@");
        },
        [] (const Literal &) -> const Var& {
            throw LogicError("Var", "Can't use operator [] on @Literal@");
        },
        [&other] (const Container &container) -> const Var& {
            auto it = container.begin();
            auto idx = other.toUint();
            if (other.index() != VNumber)
                throw LogicError("Var", "Operator [] on @Container@ must be used with a Number");
            if (container.size() <= idx)
                throw AccessError("Var," "Operator [] on @Container@ used with out of range index @" + ToString(idx) + "@");
            std::advance(it, idx);
            return *it;
        }
    }, _var);
}

oA::Var oA::Var::len(void) const
{
    return std::visit(Overload {
        [] (const Number &) -> Var {
            throw LogicError("Var", "Can't use function len on @Number@");
        },
        [] (const Literal &literal) -> Var {
            return literal.size();
        },
        [] (const Container &container) -> Var {
            return container.size();
        }
    }, _var);
}

oA::Var &oA::Var::push(const Var &value)
{
    if (std::visit(Overload {
        [] (const Number &) -> bool {
            throw LogicError("Var", "Can't use function push on @Number@");
        },
        [&value] (Literal &literal) -> bool {
            auto str = value.toString();
            literal += str;
            return !str.empty();
        },
        [this, &value] (Container &container) -> bool {
            container.emplace_back(value);
            container.back().connect([this]{ this->emit(); return true; });
            return true;
        }
    }, _var))
        this->emit();
    return *this;
}

oA::Var &oA::Var::push(Var &&value)
{
    if (std::visit(Overload {
        [] (const Number &) -> bool {
            throw LogicError("Var", "Can't use function push on @Number@");
        },
        [&value] (Literal &literal) -> bool {
            auto str = value.toString();
            literal += str;
            return !str.empty();
        },
        [this, &value] (Container &container) -> bool {
            container.emplace_back(std::move(value));
            container.back().connect([this]{ this->emit(); return true; });
            return true;
        }
    }, _var))
        this->emit();
    return *this;
}