#pragma once

#define OpenGLUse

#ifdef OpenGLUse
#define OpenGLInUse 1
class OpenGL
{
	static void Initialize();
};
#endif