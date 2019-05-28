/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Animation3D
*/

#pragma once

// Scalar types
#include "Core/Scalar.hpp"
// V3f
#include "Core/V3.hpp"
// Variant
#include "Core/Variant.hpp"
// LogicError
#include "Core/Error.hpp"

namespace oA
{
    class Animation3D;

    struct PositionAnim { oA::V3f pos; };
    struct MovementAnim { oA::V3f move; };
    struct RotationAnim { oA::V3f rotation; };
    struct MeshAnim { oA::Uint from = 0, to = 0, speed = 0; };

    using Animation3DVariant = oA::Variant<PositionAnim, MovementAnim, RotationAnim, MeshAnim>;
}

/*
    Create an Animation3D, initialize it and then visit it
*/
class oA::Animation3D
{
public:
    template<typename T>
    T &initAs(void) {
        _var = T();
        return oA::Get<T>(_var);
    }

    template<typename T>
    void visit(T &&visitor) const {
        oA::Visit(std::move(visitor), _var);
    }

private:
    Animation3DVariant _var;
};