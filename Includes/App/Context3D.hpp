/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Context
*/

#pragma once

// Scalars
#include "Core/Scalar.hpp"
// V3
#include "Core/V3.hpp"
// Strings
#include "Core/String.hpp"

namespace oA
{
    /* Drawing 3D Contexts
        Theses structures represents raw 3D drawing data used in any IRenderer3D.
    */
    struct CameraContext;
    struct CubeContext;
}

struct oA::CameraContext
{
    V3f pos, lookAt;
};

struct oA::CubeContext
{
    V3f pos, rotation;
    Float size = 0.0f;
    String texture;
};