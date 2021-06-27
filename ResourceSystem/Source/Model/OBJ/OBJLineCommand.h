#pragma once

namespace BF
{
    enum class OBJLineCommand
    {
        Invalid,
        None,
        Comment,

        MaterialLibraryInclude,
        MaterialLibraryUse,

        ObjectName,

        VertexGeometric,
        VertexTexture,
        VertexNormal,
        VertexParameter,

        SmoothShading,

        FaceElement,
    };
}