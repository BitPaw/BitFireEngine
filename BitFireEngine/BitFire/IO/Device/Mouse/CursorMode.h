#pragma once

// The mode in which the mouse pointer will be.
enum class CursorMode
{
    // Show the cursor but dont register any Input.
    Ignore,

    // Show the cursor and register Input as normal.
    Show,

    // Hide Cursor. You can still use it as normal. Not locked.
    Invisible,

    // Hide cursor and lock it at the middle.
    Locked
};