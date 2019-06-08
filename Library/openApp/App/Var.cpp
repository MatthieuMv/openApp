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
        [] (const Number &number) -> Int {
            return static_cast<Int>(number);
        },
        [] (const Literal &literal) -> Int {
            return literal.toInt();
        },
        [] (const ItemPtr &) -> Int {
            return 0;
        },
        [] (const Container &) -> Int {
            return 0;
        }
    }, _var);
}

oA::Float oA::Var::toFloat(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) -> Float {
            return number;
        },
        [] (const Literal &literal) -> Float {
            return literal.toFloat();
        },
        [] (const ItemPtr &) -> Float {
            return 0.0f;
        },
        [] (const Container &) -> Float {
            return 0.0f;
        }
    }, _var);
}

oA::String oA::Var::toString(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) -> String {
            return ToString(number);
        },
        [] (const Literal &literal) -> String {
            return literal;
        },
        [] (const ItemPtr &) -> String {
            return String();
        },
        [] (const Container &) -> String {
            return String();
        }
    }, _var);
}

oA::Var::operator bool(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) -> bool {
            return number;
        },
        [] (const Literal &literal) -> bool {
            return !literal.empty();
        },
        [] (const ItemPtr &item) -> bool {
            return item.operator bool();
        },
        [] (const Container &container) -> bool {
            return !container.empty();
        }
    }, _var);
}

bool oA::Var::operator!(void) const noexcept
{
    return std::visit(Overload {
        [] (const Number &number) -> bool {
            return !number;
        },
        [] (const Literal &literal) -> bool {
            return literal.empty();
        },
        [] (const ItemPtr &item) -> bool {
            return !item.operator bool();
        },
        [] (const Container &container) -> bool {
            return container.empty();
        }
    }, _var);
}

bool oA::Var::operator==(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> bool {
            return number == other.toFloat();
        },
        [&other] (const Literal &literal) -> bool {
            return literal == other.toString();
        },
        [this, &other] (const ItemPtr &) -> bool {
            return _var == other._var;
        },
        [this, &other] (const Container &) -> bool {
            return _var == other._var;
        }
    }, _var);
}

bool oA::Var::operator!=(const Var &other) const
{
    return !(*this == other);
}

bool oA::Var::operator<(const Var &other) const
{
    return std::visit(Overload {
        [&other] (const Number &number) -> bool {
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
        [&other] (const Number &number) -> bool {
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
        [&other] (const Number &number) -> bool {
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
        [&other] (const Number &number) -> bool {
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
    return *this = *this + other;
}

oA::Var &oA::Var::operator-=(const Var &other)
{
    return *this = *this - other;
}

oA::Var &oA::Var::operator*=(const Var &other)
{
    return *this = *this * other;
}

oA::Var &oA::Var::operator/=(const Var &other)
{
    return *this = *this / other;
}

oA::Var &oA::Var::operator%=(const Var &other)
{
    return *this = *this % other;
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