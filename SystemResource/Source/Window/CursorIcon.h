#pragma once

namespace BF
{
    enum class CursorIcon
    {
        Invalid,

        Normal,
        IBeam,
        Wait,
        Cross,
        Up,
        Hand,
        NotAllowed,

        AppStarting,

        ResizeHorizontal,
        ResizeVertical,

        ResizeClockwise,
        ResizeClockwiseCounter,
      
        ResizeAll,      
    };

    unsigned int ToCursorIcon(const CursorIcon cursorIcon);
}