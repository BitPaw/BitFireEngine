#pragma once

enum class WaveFrontLineCommand
{
    Invalid,
    None, 
    Comment,

    MaterialLibraryInclude,
    MaterialLibraryUse,

    ObjectName,

    // Use this for the First VertexGeometric
    VertexGeometricFirst,
    VertexGeometric,
    VertexTexture,
    VertexNormal,
    VertexParameter,

    SmoothShading,

    FaceElement,
};