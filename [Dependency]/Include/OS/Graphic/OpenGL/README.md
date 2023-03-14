# Open Graphics Library (OpenGL)

## Info
Installed on most systems. PXGraphics cards support it for a long time.<br>
Very old ones only support version 1.x, after Version 2.0 its downwards compartible, meaning Version 1.0 stays in the dust.

## Dependencies
- OpenGL32.DLL (Windows) -> C:/Windows/System32/

## Using the library
This library should be on most modern systems. No need for external references.
```C
#include <GL/gl.h>
```

Then, you need to create a context AND make it the current one! BOTH are needed.

||Windows|Linux|
|:-:|:-:|:-:|
|Create context | wglCreateContext | glXCreateContext |
|Use context| wglMakeCurrent | glXMakeCurrent |

## How to connect OpenGL to your code?
This library has a wierd mecanic.<br>
As this file is a system file, its never touched, a stale file.<br>
Still, we want updates and patches.. so how do we do that? Well...

Instead of updating this DLL every time, its in a "always compatible" mode.<br>
So its OpenGL Version 1.0 forever. BUT..<br>
There is some magic behind it, if you created a OpenGL context and selected it, you can fetch all modern functions.<br>
How you ask? Windows and linux both give us a function where we can ask nicely.
||Windows|Linux|
|:-:|:-:|:-:|
|Function| wglGetProcAddress | ??? |

The fetched functions do not reside in the OpenGL library anymore but come from the actual graphics card driver itself.<br>
So.. depending on your card, there can be functions that you cannot use and even special functions for just your card.


## Links
- https://www.opengl.org
