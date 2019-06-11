/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Var
*/

#include <openApp/Types/Error.hpp>
#include <openApp/App/Var.hpp>

oA::Var &oA::Var::operator=(const Var &other)
{
    _var = other._var;
    return *this;
}

oA::Var &oA::Var::operator=(Var &&other)
{
    _var = std::move(other._var);
    return *this;
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
        [] (const ItemPtr &) {
            return 0;
        },
        [] (const Container &) {
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
        [] (const ItemPtr &) {
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
        [] (const ItemPtr &) {
            return String();
        },
        [] (const Container &) {
            return String();
        }
    }, _var);
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
        [] (const ItemPtr &item) {
            return item.operator bool();
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
        [] (const ItemPtr &item) {
            return !item.operator bool();
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
        [] (const ItemPtr &) -> bool {
            throw LogicError("Var", "Can't use operator < on @Item@");
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
        [] (const ItemPtr &) -> bool {
            throw LogicError("Var", "Can't use operator <= on @Item@");
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
        [] (const ItemPtr &) -> bool {
            throw LogicError("Var", "Can't use operator > on @Item@");
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
        [] (const ItemPtr &) -> bool {
            throw LogicError("Var", "Can't use operator >= on @Item@");
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
        [] (const ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator + on @Item@");
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
        [] (const ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator - on @Item@");
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
        [] (const ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator * on @Item@");
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
        [] (const ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator / on @Item@");
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
        [] (const ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator % on @Item@");
        },
        [] (const Container &) -> Var {
            throw LogicError("Var", "Can't use operator % on @Container@");
        }
    }, _var);
}

oA::Var &oA::Var::operator+=(const Var &other)
{
    std::visit(Overload {
        [&other] (Number &number) {
            number += other.toFloat();
        },
        [&other] (Literal &literal) {
            literal += other.toString();
        },
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator += on @Item@");
        },
        [&other] (Container &) {
            throw LogicError("Var", "Can't use operator += on @Container@");
        }
    }, _var);
    return *this;
}

oA::Var &oA::Var::operator-=(const Var &other)
{
    std::visit(Overload {
        [&other] (Number &number) {
            number -= other.toFloat();
        },
        [&other] (Literal &) {
            throw LogicError("Var", "Can't use operator -= on @Literal@");
        },
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator -= on @Item@");
        },
        [&other] (Container &) {
            throw LogicError("Var", "Can't use operator -= on @Container@");
        }
    }, _var);
    return *this;
}

oA::Var &oA::Var::operator*=(const Var &other)
{
    std::visit(Overload {
        [&other] (Number &number) {
            number *= other.toFloat();
        },
        [&other] (Literal &) {
            throw LogicError("Var", "Can't use operator *= on @Literal@");
        },
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator *= on @Item@");
        },
        [&other] (Container &) {
            throw LogicError("Var", "Can't use operator *= on @Container@");
        }
    }, _var);
    return *this;
}

oA::Var &oA::Var::operator/=(const Var &other)
{
    std::visit(Overload {
        [&other] (Number &number) {
            number /= other.toFloat();
        },
        [&other] (Literal &) {
            throw LogicError("Var", "Can't use operator /= on @Literal@");
        },
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator /= on @Item@");
        },
        [&other] (Container &) {
            throw LogicError("Var", "Can't use operator /= on @Container@");
        }
    }, _var);
    return *this;
}

oA::Var &oA::Var::operator%=(const Var &other)
{
    std::visit(Overload {
        [&other] (Number &number) {
            number = static_cast<Int>(number) % other.toInt();
        },
        [&other] (Literal &) {
            throw LogicError("Var", "Can't use operator %= on @Literal@");
        },
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator %= on @Item@");
        },
        [&other] (Container &) {
            throw LogicError("Var", "Can't use operator %= on @Container@");
        }
    }, _var);
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
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator ++ on @Item@");
        },
        [] (Container &) {
            throw LogicError("Var", "Can't use operator ++ on @Container@");
        }
    }, _var);
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
        [] (ItemPtr &) {
            throw LogicError("Var", "Can't use operator -- on @Item@");
        },
        [] (Container &) {
            throw LogicError("Var", "Can't use operator -- on @Container@");
        }
    }, _var);
    return *this;
}

oA::Var oA::Var::operator++(oA::Int)
{
    return std::visit(Overload {
        [] (Number &number) -> Var {
            return number++;
        },
        [] (Literal &) -> Var {
            throw LogicError("Var", "Can't use operator ++ on @Literal@");
        },
        [] (ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator ++ on @Item@");
        },
        [] (Container &) -> Var {
            throw LogicError("Var", "Can't use operator ++ on @Container@");
        }
    }, _var);
}

oA::Var oA::Var::operator--(oA::Int)
{
    return std::visit(Overload {
        [] (Number &number) -> Var {
            return number--;
        },
        [] (Literal &) -> Var {
            throw LogicError("Var", "Can't use operator -- on @Literal@");
        },
        [] (ItemPtr &) -> Var {
            throw LogicError("Var", "Can't use operator -- on @Item@");
        },
        [] (Container &) -> Var {
            throw LogicError("Var", "Can't use operator -- on @Container@");
        }
    }, _var);
}

oA::Var &oA::Var::operator[](oA::Uint idx)
{
    return std::visit(Overload {
        [] (Number &) -> Var& {
            throw LogicError("Var", "Can't use operator [] on @Number@");
        },
        [] (Literal &) -> Var& {
            throw LogicError("Var", "Can't use operator [] on @Literal@");
        },
        [] (ItemPtr &) -> Var& {
            throw LogicError("Var", "Can't use operator [] on @Item@");
        },
        [idx] (Container &container) -> Var& {
            auto it = container.begin();
            if (container.size() <= idx)
                throw AccessError("Var::Container", "Index @" + ToString(idx) + "@ out of range");
            std::advance(it, idx);
            return *it;
        }
    }, _var);
}
