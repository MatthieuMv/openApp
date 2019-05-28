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
    struct PositionAnim { oA::V3f pos; };
    struct MovementAnim { oA::V3f move; };
    struct RotationAnim { oA::V3f rotation; };
    struct MeshAnim { oA::Uint from = 0, to = 0, speed = 0; };

    using Animation3D = oA::Variant<PositionAnim, MovementAnim, RotationAnim, MeshAnim>;
}