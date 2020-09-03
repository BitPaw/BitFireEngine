#pragma once

enum class BitMapType
{
    UnkownOrInavlid,
    // [BM] Windows 3.1x, 95, NT, ... etc.
    Windows,
    // [BA] OS/2 struct bitmap array
    OS2StructBitmapArray,
    // [CI] OS/2 struct color icon
    OS2StructColorIcon,
    // [CP] OS/2 const color pointer
    OS2ConstColorPointer,
    // [IC] OS/2 struct icon
    OS2StructIcon,
    // [PT] OS/2 pointer
    OS2Pointer
};