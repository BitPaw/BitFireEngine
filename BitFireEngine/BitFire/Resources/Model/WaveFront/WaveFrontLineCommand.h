#pragma once

enum class WaveFrontLineCommand
{
    None,
    Invalid,
    Comment,
    ObjectName,
    VertexGeometric,
    VertexTexture,
    VertexNormal,
    VertexParameter,
    SmoothShading,
    Face,
};