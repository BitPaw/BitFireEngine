#ifndef OpenGLINCLUDE
#define OpenGLINCLUDE

#include <OS/System/OSVersion.h>

#if OSUnix

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

typedef XID PXWindowID;// XID is PXWindow
typedef GLXContext OpenGLConextID;

#elif OSWindows
#include <Windows.h>
typedef HWND PXWindowID;
typedef HGLRC OpenGLConextID;
#endif

//---<OpenGL>----------------
#include <GL/gl.h>

#if OSUnix
#include <GL/glx.h>
#define OpenGLAPICallType
#elif OSWindows
#define OpenGLAPICallType APIENTRY
#endif
//---------------------------

#include <Format/Type.h>

typedef unsigned int OpenGLID;
typedef unsigned int OpenGLShaderProgramID;
typedef unsigned int OpenGLShaderID;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

#ifdef __cplusplus
extern "C"
{
#endif

	//-------------------------------------------------------------------------
	typedef enum OpenGLVersion_
	{
		OpenGLVersionInvalid,
		OpenGLVersionNone,
		OpenGLVersion1x0x0,
		OpenGLVersion1x1x0, // 1995              Texture objects, Vertex Arrays
		OpenGLVersion1x2x0, // 1998 March    16. 3D textures, BGRA and packed pixel formats, introduction of the imaging subset useful to image - processing applications
		OpenGLVersion1x2x1, // 1998 October  14. A concept of ARB extensions
		OpenGLVersion1x3x0, // 2001 August   14. Multitexturing, multisampling, texture compression
		OpenGLVersion1x4x0, // 2002 July     24. Depth textures, GLSlang
		OpenGLVersion1x5x0, // 2003 July     29. Vertex Buffer Object(VBO), Occlusion Queries
		OpenGLVersion2x0x0, // 2004 September 7. GLSL 1.10, MRT, Non Power of Two textures, Point Sprites, Two - sided stencil
		OpenGLVersion2x1x0, // 2006 July      2. GLSL 1.20, Pixel Buffer Object(PBO), sRGB Textures
		OpenGLVersion3x0x0, // 2008 August   11. GLSL 1.30, Texture Arrays, Conditional rendering, Frame Buffer Object(FBO)
		OpenGLVersion3x1x0, // 2009 March    24. GLSL 1.40, Instancing, Texture Buffer Object, Uniform Buffer Object, Primitive restart
		OpenGLVersion3x2x0, // 2009 August    3. GLSL 1.50, Geometry Shader, Multi - sampled textures
		OpenGLVersion3x3x0, // 2010 March    11. GLSL 3.30, Backports as much function as possible from the OpenGL 4.0 specification
		OpenGLVersion4x0x0, // 2010 March    11. GLSL 4.00, Tessellation on GPU, shaders with 64 - bit precision
		OpenGLVersion4x1x0, // 2010 July     26. GLSL 4.10, Developer - friendly debug outputs, compatibility with OpenGL ES 2.0
		OpenGLVersion4x2x0, // 2011 August    8. GLSL 4.20, Shaders with atomic counters, draw transform feedback instanced, shader packing, performance improvements
		OpenGLVersion4x3x0, // 2012 August    6. GLSL 4.30, Compute shaders leveraging GPU parallelism, shader storage buffer objects, high - quality ETC2 / EAC texture compression, increased memory security, a multi - application robustness extension, compatibility with OpenGL ES 3.0
		OpenGLVersion4x4x0, // 2013 July     22. GLSL 4.40, Buffer Placement Control, Efficient Asynchronous Queries, Shader Variable Layout, Efficient Multiple Object Binding, Streamlined Porting of Direct3D applications, Bindless Texture Extension, Sparse Texture Extension
		OpenGLVersion4x5x0,	// 2014 August   11. GLSL 4.50, Direct State Access(DSA), Flush Control, Robustness, OpenGL ES 3.1 API and shader compatibility, DX11 emulation features
		OpenGLVersion4x6x0	// 2017 July     31. GLSL 4.60, More efficient geometry processing and shader execution, more information, no error context, polygon offset clamp, SPIR-V, anisotropic filtering
	}
	OpenGLVersion;

	typedef enum OpenGLTextureType_
	{
		OpenGLTextureTypeInvalid,
		OpenGLTextureType1D,
		OpenGLTextureType2D,
		OpenGLTextureType2DProxy,
		OpenGLTextureType3D,
		OpenGLTextureType1DArray,
		OpenGLTextureType1DArrayProxy,
		OpenGLTextureType2DArray,
		OpenGLTextureTypeRectangle,
		OpenGLTextureTypeRectangleProxy,


		OpenGLTextureTypeCubeMap,
		OpenGLTextureTypeCubeMapProxy,
		OpenGLTextureTypeCubeMapTop,
		OpenGLTextureTypeCubeMapBottom,
		OpenGLTextureTypeCubeMapFront,
		OpenGLTextureTypeCubeMapBack,
		OpenGLTextureTypeCubeMapLeft,
		OpenGLTextureTypeCubeMapRight,


		OpenGLTextureTypeCubleMapArray,
		OpenGLTextureTypeBuffer,
		OpenGLTextureType2DMultiSample,
		OpenGLTextureType2DMultiSampleArray
	}
	OpenGLTextureType;

	typedef enum OpenGLFrameBufferMode_
	{
		OpenGLFrameBufferModeInvalid,
		OpenGLFrameBufferModeDraw,
		OpenGLFrameBufferModeRead,
		OpenGLFrameBufferModeDrawAndRead
	}
	OpenGLFrameBufferMode;

	typedef enum OpenGLShaderType_
	{
		OpenGLShaderInvalid,
		OpenGLShaderVertex,
		OpenGLShaderFragment,
		OpenGLShaderTessellationControl,
		OpenGLShaderTessellationEvaluation,
		OpenGLShaderGeometry,
		OpenGLShaderCompute
	}
	OpenGLShaderType;

	typedef enum OpenGLRenderBufferAttachmentPoint_
	{
		OpenGLRenderBufferAttachmentPointInvalid,
		OpenGLRenderBufferAttachmentPointColor,
		OpenGLRenderBufferAttachmentPointDepth,
		OpenGLRenderBufferAttachmentPointStencil
	}
	OpenGLRenderBufferAttachmentPoint;

	PXPrivate unsigned int OpenGLRenderBufferAttachmentPointToID(const OpenGLRenderBufferAttachmentPoint renderBufferAttachmentPoint);


	typedef enum OpenGLPolygonRenderOrderMode_
	{
		OpenGLPolygonRenderOrderModeInvalid,
		OpenGLPolygonRenderOrderModeClockwise,
		OpenGLPolygonRenderOrderModeCounterClockwise,
	}
	OpenGLPolygonRenderOrderMode;

	PXPrivate GLenum OpenGLPolygonRenderOrderModeToID(const OpenGLPolygonRenderOrderMode openGLPolygonRenderOrderMode);


	typedef enum OpenGLImageFormat_
	{
		OpenGLImageFormatInvalid,
		OpenGLImageFormatRGB,
		OpenGLImageFormatRGBA,
		OpenGLImageFormatBGR,
		OpenGLImageFormatBGRA,
		OpenGLImageFormatRed,
		OpenGLImageFormatGreen,
		OpenGLImageFormatBlue,
		OpenGLImageFormatAlpha,
		OpenGLImageFormatLuminance,
		OpenGLImageFormatLuminanceAlpha,
		OpenGLImageFormatColorIndex,
		OpenGLImageFormatStencilIndex,
		OpenGLImageFormatDepthComponent
	}
	OpenGLImageFormat;

	PXPrivate int OpenGLImageFormatToID(const OpenGLImageFormat imageFormat);

	typedef enum OpenGLDataType_
	{
		OpenGLTypeInvalid,

		OpenGLTypeByteSigned,  // 1 Byte, signed
		OpenGLTypeByteUnsigned, // 1 Byte, unsigned

		OpenGLTypeShortSigned,  // 2 Byte, signed
		OpenGLTypeShortUnsigned,  // 2 Byte, unsigned

		OpenGLTypeIntegerSigned,  // 4 Byte, signed
		OpenGLTypeIntegerUnsigned,  // 4 Byte, unsigned

		OpenGLTypeFloat,  // 4 Byte
		OpenGLTypeDouble,  // 8 Byte
	}
	OpenGLDataType;

	PXPrivate int OpenGLDataTypeToID(const OpenGLDataType dataType);

	typedef enum OpenGLRenderBufferFormat_
	{
		OpenGLRenderBufferFormatInvalid,
		OpenGLRenderBufferFormatDepth24Stencil8
	}
	OpenGLRenderBufferFormat;

	PXPrivate int OpenGLRenderBufferFormatToID(const OpenGLRenderBufferFormat dataType);


	typedef enum OpenGLTextureParameterMode_
	{
		OpenGLTextureParameterModoInvalid,
		OpenGLDEPTH_STENCIL_TextureMODE,
		OpenGLTextureBASE_LEVEL,
		OpenGLTextureCOMPARE_FUNC,
		OpenGLTextureCOMPARE_MODE,
		OpenGLTextureLOD_BIAS,
		OpenGLTextureMIN_FILTER,
		OpenGLTextureMAG_FILTER,
		OpenGLTextureMIN_LOD,
		OpenGLTextureMAX_LOD,
		OpenGLTextureMAX_LEVEL,
		OpenGLTextureSWIZZLE_R,
		OpenGLTextureSWIZZLE_G,
		OpenGLTextureSWIZZLE_B,
		OpenGLTextureSWIZZLE_A,
		OpenGLTextureWRAP_S,
		OpenGLTextureWRAP_T,
		OpenGLTextureWRAP_R,
		OpenGLTextureBORDER_COLOR,
		OpenGLTextureSWIZZLE_RGBA,
	}
	OpenGLTextureParameterMode;

	PXPrivate GLenum OpenGLTextureParameterModeToID(const OpenGLTextureParameterMode textureParameterMode);

	typedef enum OpenGLRenderMode_
	{
		OpenGLRenderInvalid,
		OpenGLRenderPoints,
		OpenGLRenderLines,
		OpenGLRenderLineLoop,
		OpenGLRenderLineStrip,
		OpenGLRenderTriangles,
		OpenGLRenderTriangleStrip,
		OpenGLRenderTriangleFan,
		OpenGLRenderQuads,
		OpenGLRenderQuadStrip,
		OpenGLRenderPolygon
	}
	OpenGLRenderMode;

	PXPrivate int OpenGLRenderModeToID(const OpenGLRenderMode openGLRenderMode);



	typedef enum OpenGLBufferType_
	{
		OpenGLBufferArray,//Vertex attributes
		OpenGLBufferAtomicCounter, 	//Atomic counter storage
		OpenGLBufferCopyRead 	,//Buffer copy source
		OpenGLBufferCopyWrite 	,//Buffer copy destination
		OpenGLBufferDispatchIndirect, //	Indirect compute dispatch commands
		OpenGLBufferDrawIndirect,	//Indirect command arguments
		OpenGLBufferElementArray,	//Vertex array indices
		OpenGLBufferPixelPack 	,//Pixel read target
		OpenGLBufferPixelUnpack ,//	Texture data source
		OpenGLBufferQuery,//Query result buffer
		OpenGLBufferShaderStorage ,	//Read - write storage for shaders
		OpenGLBufferTexture 	,// Texture data buffer
		OpenGLBufferTransformFeedback,//	Transform feedback buffer
		OpenGLBufferUniform
	}
	OpenGLBufferType;

	PXPrivate int OpenGLBufferTypeToID(const OpenGLBufferType openGLBufferType);

	typedef enum OpenGLTextureParameterValue_
	{
		OpenGLTextureParameterValueInvalid,

		OpenGLTextureParameterValueNEAREST,
		OpenGLTextureParameterValueLINEAR,

		OpenGLTextureParameterValueClampToEdge,
		OpenGLTextureParameterValueClampToBorder,
		OpenGLTextureParameterValueMirroredRepeat,
		OpenGLTextureParameterValueRepeat,
		OpenGLTextureParameterValueMirrorClampToEdge,
		OpenGLTextureParameterValueWrapS,
		OpenGLTextureParameterValueWrapR
	}
	OpenGLTextureParameterValue;

	PXPrivate GLint OpenGLTextureParameterValueToID(const OpenGLTextureParameterValue openGLTextureParameterValue);


	typedef enum OpenGLStoreMode_
	{
		OpenGLStoreInvalid,
		OpenGLStoreStreamDraw,
		OpenGLStoreStreamRead,
		OpenGLStoreStreamCopy,
		OpenGLStoreStaticDraw,
		OpenGLStoreStaticREAD,
		OpenGLStoreStaticCOPY,
		OpenGLStoreDynamicDraw,
		OpenGLStoreDynamicRead,
		OpenGLStoreDynamicCopy
	}
	OpenGLStoreMode;

	PXPrivate int OpenGLStoreModeToID(const OpenGLStoreMode openGLStoreMode);


	typedef enum OpenGLDrawOrderMode_
	{
		OpenGLDrawOrderModeInvalid,
		OpenGLDrawOrderModeClockwise,
		OpenGLDrawOrderModeCounterClockwise
	}
	OpenGLDrawOrderMode;


	PXPrivate GLenum OpenGLDrawOrderToID(const OpenGLDrawOrderMode openGLDrawOrderMode);


	typedef enum OpenGLToggle_
	{
		OpenGLToggleInvalid,

		OpenGLToggleTextureCubeMapSeamless,

		OpenGLALPHA_TEST, // If enabled, do alpha testing. See glAlphaFunc.
		OpenGLAUTO_NORMAL, // If enabled, generate normal vectors when either OpenGLMAP2_VERTEX_3 or OpenGLMAP2_VERTEX_4 is used to generate vertices. See glMap2.
		OpenGLBLEND, // If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc.
		OpenGLCLIP_PLANEi, // If enabled, clip geometry against user-defined clipping plane i. See glClipPlane.
		OpenGLCOLOR_LOGIC_OP, // If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values. See glLogicOp.
		OpenGLCOLOR_MATERIAL, // If enabled, have one or more material parameters track the current color. See glColorMaterial.
		OpenGLCOLOR_SUM, // If enabled and no fragment shader is active, add the secondary color value to the computed fragment color. See glSecondaryColor.
		OpenGLCOLOR_TABLE, // If enabled, perform a color table lookup on the incoming RGBA color values. See glColorTable.
		OpenGLCONVOLUTION_1D, // If enabled, perform a 1D convolution operation on incoming RGBA color values. See glConvolutionFilter1D.
		OpenGLCONVOLUTION_2D, // If enabled, perform a 2D convolution operation on incoming RGBA color values. See glConvolutionFilter2D.
		OpenGLCULL_FACE, // If enabled, cull polygons based on their winding in window coordinates. See glCullFace.
		OpenGLDEPTH_TEST, // If enabled, do depth comparisons and update the depth buffer. Note that even , // If the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated , // If the depth test is disabled. See glDepthFunc and glDepthRange.
		OpenGLDITHER, // If enabled, dither color components or indices before they are written to the color buffer.
		OpenGLFOG, // If enabled and no fragment shader is active, blend a fog color into the post-texturing color. See glFog.
		OpenGLHISTOGRAM, // If enabled, histogram incoming RGBA color values. See glHistogram.
		OpenGLINDEX_LOGIC_OP, // If enabled, apply the currently selected logical operation to the incoming index and color buffer indices. See glLogicOp.
		OpenGLLIGHTi, // If enabled, include light i in the evaluation of the lighting equation. See glLightModel and glLight.
		OpenGLLIGHTING, // If enabled and no vertex shader is active, use the current lighting parameters to compute the vertex color or index. Otherwise, simply associate the current color or index with each vertex. See glMaterial, glLightModel, and glLight.
		OpenGLLINE_SMOOTH, // If enabled, draw lines with correct filtering. Otherwise, draw aliased lines. See glLineWidth.
		OpenGLLINE_STIPPLE, // If enabled, use the current line stipple pattern when drawing lines. See glLineStipple.
		OpenGLMAP1_COLOR_4, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate RGBA values. See glMap1.
		OpenGLMAP1_INDEX, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate color indices. See glMap1.
		OpenGLMAP1_NORMAL, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate normals. See glMap1.
		OpenGLMAP1_TEXTURE_COORD_1, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate s texture coordinates. See glMap1.
		OpenGLMAP1_TEXTURE_COORD_2, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate s and t texture coordinates. See glMap1.
		OpenGLMAP1_TEXTURE_COORD_3, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate s, t, and r texture coordinates. See glMap1.
		OpenGLMAP1_TEXTURE_COORD_4, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate s, t, r, and q texture coordinates. See glMap1.
		OpenGLMAP1_VERTEX_3, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate x, y, and z vertex coordinates. See glMap1.
		OpenGLMAP1_VERTEX_4, // If enabled, calls to glEvalCoord1, glEvalMesh1, and glEvalPoint1 generate homogeneous x, y, z, and w vertex coordinates. See glMap1.
		OpenGLMAP2_COLOR_4, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate RGBA values. See glMap2.
		OpenGLMAP2_INDEX, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate color indices. See glMap2.
		OpenGLMAP2_NORMAL, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate normals. See glMap2.
		OpenGLMAP2_TEXTURE_COORD_1, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate s texture coordinates. See glMap2.
		OpenGLMAP2_TEXTURE_COORD_2, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate s and t texture coordinates. See glMap2.
		OpenGLMAP2_TEXTURE_COORD_3, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate s, t, and r texture coordinates. See glMap2.
		OpenGLMAP2_TEXTURE_COORD_4, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate s, t, r, and q texture coordinates. See glMap2.
		OpenGLMAP2_VERTEX_3, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate x, y, and z vertex coordinates. See glMap2.
		OpenGLMAP2_VERTEX_4, // If enabled, calls to glEvalCoord2, glEvalMesh2, and glEvalPoint2 generate homogeneous x, y, z, and w vertex coordinates. See glMap2.
		OpenGLMINMAX, // If enabled, compute the minimum and maximum values of incoming RGBA color values. See glMinmax.
		OpenGLMULTISAMPLE, // If enabled, use multiple fragment samples in computing the final color of a pixel. See glSampleCoverage.
		OpenGLNORMALIZE, // If enabled and no vertex shader is active, normal vectors are normalized to unit length after transformation and before lighting. This method is generally less efficient than OpenGLRESCALE_NORMAL. See glNormal and glNormalPointer.
		OpenGLPOINT_SMOOTH, // If enabled, draw points with proper filtering. Otherwise, draw aliased points. See glPointSize.
		OpenGLPOINT_SPRITE, // If enabled, calculate texture coordinates for points based on texture environment and point parameter settings. Otherwise texture coordinates are constant across points.
		OpenGLPOLYGON_OFFSET_FILL, // If enabled, and , // If the polygon is rendered in OpenGLFILL mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
		OpenGLPOLYGON_OFFSET_LINE, // If enabled, and , // If the polygon is rendered in OpenGLLINE mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
		OpenGLPOLYGON_OFFSET_POINT, // If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, , // If the polygon is rendered in OpenGLPOINT mode. See glPolygonOffset.
		OpenGLPOLYGON_SMOOTH, // If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back.
		OpenGLPOLYGON_STIPPLE, // If enabled, use the current polygon stipple pattern when rendering polygons. See glPolygonStipple.
		OpenGLPOST_COLOR_MATRIX_COLOR_TABLE, // If enabled, perform a color table lookup on RGBA color values after color matrix transformation. See glColorTable.
		OpenGLPOST_CONVOLUTION_COLOR_TABLE, // If enabled, perform a color table lookup on RGBA color values after convolution. See glColorTable.
		OpenGLRESCALE_NORMAL, // If enabled and no vertex shader is active, normal vectors are scaled after transformation and before lighting by a factor computed from the modelview matrix. , // If the modelview matrix scales space un, // Iformly, this has the effect of restoring the transformed normal to unit length. This method is generally more efficient than OpenGLNORMALIZE. See glNormal and glNormalPointer.
		OpenGLSAMPLE_ALPHA_TO_COVERAGE, // If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.
		OpenGLSAMPLE_ALPHA_TO_ONE, // If enabled, each sample alpha value is replaced by the maximum representable alpha value.
		OpenGLSAMPLE_COVERAGE, // If enabled, the fragment's coverage is ANDed with the temporary coverage value. , // If OpenGLSAMPLE_COVERAGE_INVERT is set to OpenGLTRUE, invert the coverage value. See glSampleCoverage.
		OpenGLSEPARABLE_2D, // If enabled, perform a two-dimensional convolution operation using a separable convolution filter on incoming RGBA color values. See glSeparableFilter2D.
		OpenGLSCISSOR_TEST, // If enabled, discard fragments that are outside the scissor rectangle. See glScissor.
		OpenGLSTENCIL_TEST, // If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp.
		OpenGLTEXTURE_1D, // If enabled and no fragment shader is active, one-dimensional texturing is performed (unless two- or three-dimensional or cube-mapped texturing is also enabled). See glTexImage1D.
		OpenGLTEXTURE_2D, // If enabled and no fragment shader is active, two-dimensional texturing is performed (unless three-dimensional or cube-mapped texturing is also enabled). See glTexImage2D.
		OpenGLTEXTURE_3D, // If enabled and no fragment shader is active, three-dimensional texturing is performed (unless cube-mapped texturing is also enabled). See glTexImage3D.
		OpenGLTEXTURE_CUBE_MAP, // If enabled and no fragment shader is active, cube-mapped texturing is performed. See glTexImage2D.
		OpenGLTEXTURE_GEN_Q, // If enabled and no vertex shader is active, the q texture coordinate is computed using the texture generation function defined with glTexGen. Otherwise, the current q texture coordinate is used. See glTexGen.
		OpenGLTEXTURE_GEN_R, // If enabled and no vertex shader is active, the r texture coordinate is computed using the texture generation function defined with glTexGen. Otherwise, the current r texture coordinate is used. See glTexGen.
		OpenGLTEXTURE_GEN_S, // If enabled and no vertex shader is active, the s texture coordinate is computed using the texture generation function defined with glTexGen. Otherwise, the current s texture coordinate is used. See glTexGen.
		OpenGLTEXTURE_GEN_T, // If enabled and no vertex shader is active, the t texture coordinate is computed using the texture generation function defined with glTexGen. Otherwise, the current t texture coordinate is used. See glTexGen.
		OpenGLVERTEX_PROGRAM_POINT_SIZE, // If enabled and a vertex shader is active, then the derived point size is taken from the (potentially clipped) shader builtin OpenGLPointSize and clamped to the implementation-dependent point size range.
		OpenGLVERTEX_PROGRAM_TWO_SIDE// If enabled and a vertex shader is active, it spec, // Ifies that the GL will choose between front and back colors based on the polygon's face direction of which the vertex being shaded is a part. It has no effect on points or lines.
	}
	OpenGLToggle;

	PXPrivate int OpenGLToggleToID(const OpenGLToggle openGLToggle);


	typedef enum OpenGLStringName_
	{
		OpenGLStringNameInvalid,
		OpenGLStringNameVendor,
		OpenGLStringNameRenderer,
		OpenGLStringNameVersion,
		OpenGLStringNameShadingLanguage,
		OpenGLStringNameExtensions
	}
	OpenGLStringName;

	typedef const GLubyte* (*OpenGLStringFunction)(GLenum name); // glGetString

	PXPrivate unsigned int OpenGLStringNameToID(const OpenGLStringName stringName);

	PXPublic const char* OpenGLStringGet(const OpenGLStringName stringName);


	//-------------------------------------------------------------------------

	//---<OpenGL v.1.2.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.2.1>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.3.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.4.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.5.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.2.0.0>------------------------------------------------------
	PXPublic unsigned int OpenGLTextureTypeToID(const OpenGLTextureType openGLTextureType);

	typedef unsigned int (OpenGLAPICallType* OpenGLShaderProgramCreateFunction)();
	typedef void (OpenGLAPICallType* OpenGLShaderProgramUseFunction)(unsigned int program);
	typedef void (OpenGLAPICallType* OpenGLShaderProgramDeleteFunction)(GLuint program); // glDeleteProgram
	typedef void (OpenGLAPICallType* OpenGLShaderSourceFunction)(unsigned int shader, int count, const char** string, const int* length);
	typedef GLuint(OpenGLAPICallType* OpenGLShaderCreateFunction)(GLenum shaderType); // glCreateShader
	typedef void (OpenGLAPICallType* OpenGLShaderCompileFunction)(GLuint shader);
	typedef void (OpenGLAPICallType* OpenGLShaderGetivFunction)(GLuint shader, GLenum pname, GLint* params);
	typedef void (OpenGLAPICallType* OpenGLShaderLogInfoGetFunction)(GLuint shader, GLsizei maxLength, GLsizei* length, char* infoLog);
	typedef void (OpenGLAPICallType* OpenGLShaderDeleteFunction)(GLuint shader);
	typedef void (OpenGLAPICallType* OpenGLAttachShaderFunction)(GLuint program, GLuint shader); // glAttachShader
	typedef void (OpenGLAPICallType* OpenGLLinkProgramFunction)(GLuint program); // glLinkProgram
	typedef void (OpenGLAPICallType* OpenGLValidateProgramFunction)(GLuint program); // glValidateProgram
	typedef void (OpenGLAPICallType* OpenGLActiveTextureFunction)(GLenum texture); // glActiveTexture
	typedef void (OpenGLAPICallType* OpenGLGenBuffersFunction)(GLsizei n, GLuint* buffers); // glGenBuffers
	typedef void (OpenGLAPICallType* OpenGLBindBufferFunction)(GLenum target, GLuint buffer);
	typedef void (OpenGLAPICallType* OpenGLBufferDataFunction)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

	typedef void (OpenGLAPICallType* OpenGLVertexAttribPointerFunction)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	typedef void (OpenGLAPICallType* OpenGLVertexAttribArrayEnableFunction)(GLuint index); // glEnableVertexAttribArray
	typedef void (OpenGLAPICallType* OpenGLVertexAttribArrayDisableFunction)(GLuint index); // glDisableVertexAttribArray

	typedef void (OpenGLAPICallType* OpenGLDisableVertexArrayAttribFunction)(GLuint vaobj, GLuint index);
	typedef GLint(OpenGLAPICallType* OpenGLGetUniformLocation)(GLuint program, const char* name);
	typedef void (OpenGLAPICallType* OpenGLUniform1fFunction)(GLint location, GLfloat v0);
	typedef void (OpenGLAPICallType* OpenGLUniform1fvFunction)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniform1iFunction)(GLint location, GLint v0);
	typedef void (OpenGLAPICallType* OpenGLUniform1ivFunction)(GLint location, GLsizei count, const GLint* value);
	typedef void (OpenGLAPICallType* OpenGLUniform2fFunction)(GLint location, GLfloat v0, GLfloat v1);
	typedef void (OpenGLAPICallType* OpenGLUniform2fvFunction)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniform2iFunction)(GLint location, GLint v0, GLint v1);
	typedef void (OpenGLAPICallType* OpenGLUniform2ivFunction)(GLint location, GLsizei count, const GLint* value);
	typedef void (OpenGLAPICallType* OpenGLUniform3fFunction)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	typedef void (OpenGLAPICallType* OpenGLUniform3fvFunction)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniform3iFunction)(GLint location, GLint v0, GLint v1, GLint v2);
	typedef void (OpenGLAPICallType* OpenGLUniform3ivFunction)(GLint location, GLsizei count, const GLint* value);
	typedef void (OpenGLAPICallType* OpenGLUniform4fFunction)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	typedef void (OpenGLAPICallType* OpenGLUniform4fvFunction)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniform4iFunction)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	typedef void (OpenGLAPICallType* OpenGLUniform4ivFunction)(GLint location, GLsizei count, const GLint* value);
	typedef void (OpenGLAPICallType* OpenGLUniformMatrix2fvFunction)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniformMatrix3fvFunction)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (OpenGLAPICallType* OpenGLUniformMatrix4fvFunction)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	typedef void (OpenGLAPICallType* OpenGLTextureCreateFunction)(GLsizei n, GLuint* textures); // glGenTextures
	typedef void (OpenGLAPICallType* OpenGLTextureBindFunction)(GLenum target, GLuint texture); // glBindTexture
	typedef void (OpenGLAPICallType* OpenGLTextureDeleteFunction)(GLsizei n, const GLuint* textures); // glDeleteTextures
    //-------------------------------------------------------------------------

	//---<OpenGL v.2.1.0>------------------------------------------------------
    //-------------------------------------------------------------------------

    //---<OpenGL v.3.0.0>------------------------------------------------------
	typedef void (OpenGLAPICallType* OpenGLFrameBufferCreateFunction)(GLsizei n, GLuint* ids); // glGenFramebuffers
	typedef void (OpenGLAPICallType* OpenGLFrameBufferDeleteFunction)(GLsizei n, GLuint* framebuffers); // glDeleteFramebuffers
	typedef void (OpenGLAPICallType* OpenGLFrameBufferBindFunction)(GLenum target, GLuint framebuffer); // glBindFramebuffer

	typedef void (OpenGLAPICallType* OpenGLRenderBufferCreateFunction)(GLsizei n, GLuint* renderbuffers); // glGenRenderbuffers
	typedef void (OpenGLAPICallType* OpenGLRenderBufferBindFunction)(GLenum target, GLuint renderbuffer); // glBindRenderbuffer
	typedef void (OpenGLAPICallType* OpenGLRenderBufferDeleteFunction)(GLsizei n, GLuint* renderbuffers); // glDeleteRenderbuffers
	typedef void (OpenGLAPICallType* OpenGLRenderBufferStorageFunction)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height); // glRenderbufferStorage

	typedef void (OpenGLAPICallType* OpenGLFrameBufferLinkTexture2DFunction)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	typedef GLuint (OpenGLAPICallType* OpenGLFrameBufferLinkRenderBufferFunction)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

	typedef void (OpenGLAPICallType* OpenGLGenVertexArraysFunction)(GLsizei n, GLuint* arrays);
	typedef void (OpenGLAPICallType* OpenGLBindVertexArrayFunction)(GLuint arrayID);
	typedef void (OpenGLAPICallType* OpenGLVertexAttribIPointerFunction)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef const GLubyte* (OpenGLAPICallType* OpenGLStringIFunction)(GLenum name, GLuint index); // glGetStringi

	//-------------------------------------------------------------------------

	//---<OpenGL v.3.1.0>------------------------------------------------------
	typedef void (OpenGLAPICallType* OpenGLDrawArraysInstancedFunction)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount); // glDrawArraysInstanced
	//-------------------------------------------------------------------------

	//---<OpenGL v.3.2.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.3.3.0>------------------------------------------------------
	typedef void  (OpenGLAPICallType* OpenGLVertexAttribDivisorFunction)(GLuint index, GLuint divisor); // glVertexAttribDivisor
	//-------------------------------------------------------------------------



	//---<OpenGL v.4.0.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.1.0>------------------------------------------------------
	typedef void (OpenGLAPICallType * OpenGLVertexAttribLPointerFunction)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.2.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.3.0>------------------------------------------------------
	typedef void (OpenGLAPICallType*DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	typedef void (OpenGLAPICallType*OpenGLDebugMessageFunction)(DEBUGPROC callback, const void* userParam); // Set
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.4.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.5.0>------------------------------------------------------
	typedef void (OpenGLAPICallType*OpenGLNamedBufferData)(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
	typedef void (OpenGLAPICallType*OpenGLEnableVertexAttribArray)(GLuint index);
	typedef void (OpenGLAPICallType*OpenGLEnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
	//-------------------------------------------------------------------------

	//---<OpenGL v.4.6.0>------------------------------------------------------
	//-------------------------------------------------------------------------


	//---<Extensions>----------------------------------------------------------
#if OSUnix

#elif OSWindows
	typedef const char* (OpenGLAPICallType* OpenGLStringGetExtensionsARB)(HDC hdc); // wglGetExtensionsStringARB
#endif
















	typedef struct OpenGLContext_
	{
		OpenGLConextID OpenGLConext;

		char Vendor[64];
		char Renderer[64];
		char VersionText[64];
		char GLSLVersionText[64];
		OpenGLVersion Version;

        void* AttachedWindow;




		//---<OpenGL v.1.2.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.1.2.1>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.1.3.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.1.4.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.1.5.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.2.0.0>------------------------------------------------------
		OpenGLShaderProgramCreateFunction	OpenGLShaderProgramCreateCallBack;
		OpenGLShaderProgramUseFunction	OpenGLShaderProgramUseCallBack;
		OpenGLShaderProgramDeleteFunction OpenGLShaderProgramDeleteCallBack;
		OpenGLShaderCreateFunction OpenGLShaderCreateCallBack;
		OpenGLShaderSourceFunction	OpenGLShaderSourceCallBack;
		OpenGLShaderCompileFunction	OpenGLShaderCompileCallBack;
		OpenGLShaderGetivFunction	OpenGLShaderGetivCallBack;
		OpenGLShaderLogInfoGetFunction	OpenGLShaderLogInfoGetCallBack;
		OpenGLShaderDeleteFunction	OpenGLShaderDeleteCallBack;
		OpenGLAttachShaderFunction	OpenGLAttachShaderCallBack;
		OpenGLLinkProgramFunction	OpenGLLinkProgramCallBack;
		OpenGLValidateProgramFunction	OpenGLValidateProgramCallBack;
		OpenGLActiveTextureFunction	OpenGLActiveTextureCallBack;
		OpenGLGenBuffersFunction	OpenGLGenBuffersCallBack;
		OpenGLBindBufferFunction	OpenGLBindBufferCallBack;
		OpenGLBufferDataFunction	OpenGLBufferDataCallBack;
		OpenGLVertexAttribPointerFunction OpenGLVertexAttribPointerCallBack;
		OpenGLVertexAttribArrayEnableFunction OpenGLVertexAttribArrayEnableCallBack;
		OpenGLVertexAttribArrayDisableFunction OpenGLVertexAttribArrayDisableCallBack;
		OpenGLDisableVertexArrayAttribFunction	OpenGLDisableVertexArrayAttribCallBack;
		OpenGLGetUniformLocation	OpenGLGetUniformLocation;
		OpenGLUniform1fFunction	OpenGLUniform1fCallBack;
		OpenGLUniform1fvFunction	OpenGLUniform1fvCallBack;
		OpenGLUniform1iFunction	OpenGLUniform1iCallBack;
		OpenGLUniform1ivFunction	OpenGLUniform1ivCallBack;
		OpenGLUniform2fFunction	OpenGLUniform2fCallBack;
		OpenGLUniform2fvFunction	OpenGLUniform2fvCallBack;
		OpenGLUniform2iFunction	OpenGLUniform2iCallBack;
		OpenGLUniform2ivFunction	OpenGLUniform2ivCallBack;
		OpenGLUniform3fFunction	OpenGLUniform3fCallBack;
		OpenGLUniform3fvFunction	OpenGLUniform3fvCallBack;
		OpenGLUniform3iFunction	OpenGLUniform3iCallBack;
		OpenGLUniform3ivFunction	OpenGLUniform3ivCallBack;
		OpenGLUniform4fFunction	OpenGLUniform4fCallBack;
		OpenGLUniform4fvFunction	OpenGLUniform4fvCallBack;
		OpenGLUniform4iFunction	OpenGLUniform4iCallBack;
		OpenGLUniform4ivFunction	OpenGLUniform4ivCallBack;
		OpenGLUniformMatrix2fvFunction	OpenGLUniformMatrix2fvCallBack;
		OpenGLUniformMatrix3fvFunction	OpenGLUniformMatrix3fvCallBack;
		OpenGLUniformMatrix4fvFunction OpenGLUniformMatrix4fvCallBack;

		OpenGLTextureCreateFunction OpenGLTextureCreateCallBack;
		OpenGLTextureBindFunction OpenGLTextureBindCallBack;
		OpenGLTextureDeleteFunction OpenGLTextureDeleteCallBack;
		//-------------------------------------------------------------------------

		//---<OpenGL v.2.1.0>------------------------------------------------------
		//-------------------------------------------------------------------------

		//---<OpenGL v.3.0.0>------------------------------------------------------
		OpenGLFrameBufferCreateFunction OpenGLFrameBufferCreateCallBack;
		OpenGLFrameBufferDeleteFunction OpenGLFrameBufferDeleteCallBack;
		OpenGLFrameBufferBindFunction OpenGLFrameBufferBindCallBack;

		OpenGLRenderBufferCreateFunction OpenGLRenderBufferCreateCallBack;
		OpenGLRenderBufferBindFunction  OpenGLRenderBufferBindCallBack;
		OpenGLRenderBufferDeleteFunction OpenGLRenderBufferDeleteCallBack;
		OpenGLRenderBufferStorageFunction OpenGLRenderBufferStorageCallBack;
		OpenGLFrameBufferLinkTexture2DFunction OpenGLFrameBufferLinkTexture2DCallBack;
		OpenGLFrameBufferLinkRenderBufferFunction OpenGLFrameBufferLinkRenderBufferCallBack;

		OpenGLGenVertexArraysFunction OpenGLGenVertexArraysCallBack;
		OpenGLBindVertexArrayFunction OpenGLBindVertexArrayCallBack;
		OpenGLVertexAttribIPointerFunction OpenGLVertexAttribIPointerCallBack;

		OpenGLStringIFunction OpenGLStringICallBack;
		//-------------------------------------------------------------------------

		//---<OpenGL v.3.1.0>------------------------------------------------------
		OpenGLDrawArraysInstancedFunction OpenGLDrawArraysInstancedCallBack;
		//-------------------------------------------------------------------------

		//---<OpenGL v.3.2.0>------------------------------------------------------
		//-------------------------------------------------------------------------

		//---<OpenGL v.3.3.0>------------------------------------------------------
		OpenGLVertexAttribDivisorFunction OpenGLVertexAttribDivisorCallBack;
		//-------------------------------------------------------------------------		

		//---<OpenGL v.4.0.0>------------------------------------------------------
		//-------------------------------------------------------------------------

		//---<OpenGL v.4.1.0>------------------------------------------------------
		OpenGLVertexAttribLPointerFunction	OpenGLVertexAttribLPointerCallBack;
		//-------------------------------------------------------------------------

		//---<OpenGL v.4.2.0>------------------------------------------------------
		//-------------------------------------------------------------------------

		//---<OpenGL v.4.3.0>------------------------------------------------------
		OpenGLDebugMessageFunction OpenGLDebugMessageCallback;
		//-------------------------------------------------------------------------

		//---<OpenGL v.4.4.0>------------------------------------------------------
		//-------------------------------------------------------------------------

		//---<OpenGL v.4.5.0>------------------------------------------------------

		//-------------------------------------------------------------------------

		//---<OpenGL v.4.6.0>------------------------------------------------------
		//-------------------------------------------------------------------------
	}
	OpenGLContext;

	//---<Utility>-------------------------------------------------------------
	PXPublic void OpenGLContextConstruct(OpenGLContext* const openGLContext);
	PXPublic void OpenGLContextDestruct(OpenGLContext* const openGLContext);


	PXPublic void OpenGLContextSet(OpenGLContext* const openGLContext, const OpenGLContext* const openGLContextSoure);
	PXPublic void OpenGLContextCopy(OpenGLContext* const openGLContext, const OpenGLContext* const openGLContextSoure);

	PXPublic PXBool OpenGLContextCreateForWindow(OpenGLContext* const openGLContext);
	PXPublic void OpenGLContextCreateWindowless(OpenGLContext* const openGLContext, const PXSize width, const PXSize height);
	PXPublic void OpenGLContextSelect(OpenGLContext* const openGLContext);
	PXPublic PXBool OpenGLContextDeselect(OpenGLContext* const openGLContext);
	PXPublic void OpenGLContextRelease(OpenGLContext* const openGLContext);

	PXPublic void OpenGLRenderBufferSwap(OpenGLContext* const openGLContext);

	PXPublic void OpenGLFlush(OpenGLContext* const openGLContext);
	PXPublic void OpenGLViewSize(OpenGLContext* const openGLContext, const PXSize x, const PXSize y, const PXSize width, const PXSize height);


	PXPublic void OpenGLPolygonRenderOrder(const OpenGLContext* const openGLContext, const OpenGLPolygonRenderOrderMode openGLPolygonRenderOrderMode);

	PXPublic void OpenGLSettingChange(OpenGLContext* const openGLContext, const OpenGLToggle toggle, const PXBool state);

	PXPublic void OpenGLDrawOrder(OpenGLContext* const openGLContext, const OpenGLDrawOrderMode openGLDrawOrderMode);

	PXPublic void OpenGLClearColor(OpenGLContext* const openGLContext, const float red, const float green, const float blue, const float alpha);
	PXPublic void OpenGLClear(OpenGLContext* const openGLContext, const unsigned int clearID);
	PXPublic void OpenGLDrawScaleF(OpenGLContext* const openGLContext, const float x, const float y, const float z);
	PXPublic void OpenGLDrawBegin(OpenGLContext* const openGLContext, const OpenGLRenderMode openGLRenderMode);
	PXPublic void OpenGLDrawVertexXYZF(OpenGLContext* const openGLContext, const float x, const float y, const float z);
	PXPublic void OpenGLDrawColorRGBF(OpenGLContext* const openGLContext, const float red, const float green, const float blue);
	PXPublic void OpenGLDrawEnd(OpenGLContext* const openGLContext);

	PXPublic void OpenGLTextureParameter(OpenGLContext* const openGLContext, const OpenGLTextureType textureType, const OpenGLTextureParameterMode pname, const OpenGLTextureParameterValue openGLTextureParameterValue);
	PXPublic void OpenGLTextureParameterI(OpenGLContext* const openGLContext, const OpenGLTextureType textureType, const OpenGLTextureParameterMode pname, const int param);
	PXPublic void OpenGLTextureParameterF(OpenGLContext* const openGLContext, const OpenGLTextureType textureType, const OpenGLTextureParameterMode pname, const float param);

	PXPrivate OpenGLVersion OpenGLVersionParse(const unsigned int versionID);
	PXPrivate void OpenGLCacheFunction(void** loadList, PXSize* currentSize, char* name, void* functionADress);
	PXPrivate const void* const OpenGLFunctionAdressFetch(const char* const functionName);

	PXPublic void OpenGLAPICallType OpenGLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	//-------------------------------------------------------------------------

	// render

	PXPublic void OpenGLDrawArrays(const OpenGLContext* const openGLContext, const OpenGLRenderMode renderMode, const PXSize offset, const PXSize amount);
	PXPublic void OpenGLDrawElements(const OpenGLContext* const openGLContext, const OpenGLRenderMode renderMode, const PXSize amount, const OpenGLDataType openGLDataType, const void* const indexList);


	
	PXPublic void OpenGLDrawArraysInstanced(const OpenGLContext* const openGLContext, const OpenGLRenderMode renderMode, const PXSize startOffset, const PXSize amount, const PXSize instanceAmount);

	//---<Texture>-------------------------------------------------------------
	PXPublic void OpenGLTextureActivate(OpenGLContext* const openGLContext, const unsigned int index);
	PXPublic void OpenGLTextureCreate(OpenGLContext* const openGLContext, GLsizei n, GLuint* textures); // glGenTextures
	PXPublic void OpenGLTextureBind(OpenGLContext* const openGLContext, const OpenGLTextureType textureType, GLuint texture); // glBindTexture
	PXPublic void OpenGLTextureUnbind(OpenGLContext* const openGLContext, const OpenGLTextureType textureType);
	PXPublic void OpenGLTextureDelete(OpenGLContext* const openGLContext, GLsizei n, const GLuint* textures); // glDeleteTextures
	PXPublic void OpenGLTextureData2D
	(
		OpenGLContext* const openGLContext,
		const OpenGLTextureType glTextureType,
		const unsigned int level,
		const OpenGLImageFormat glImageFormatInternal,
		const PXSize width,
		const PXSize height,
		const OpenGLImageFormat glImageFormatInput,
		const OpenGLDataType glDataType,
		const void* const imageData
	);
	//-------------------------------------------------------------------------


	//---<Shader>-----------------------------------------------------------------
	PXPublic unsigned int OpenGLShaderTypeToID(const OpenGLShaderType openGLShaderType);
	PXPublic OpenGLShaderID OpenGLShaderCreate(OpenGLContext* const openGLContext, const OpenGLShaderType openGLShaderType);
	PXPublic void OpenGLShaderSource(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, const PXSize count, const char** string, PXSize* const length);
	PXPublic unsigned char OpenGLShaderCompile(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID);
	PXPublic void OpenGLShaderGetiv(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, GLenum pname, GLint* params);
	PXPublic void OpenGLShaderLogInfoGet(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, GLsizei maxLength, GLsizei* length, char* infoLog);
	PXPublic void OpenGLShaderDelete(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID);

	PXPublic OpenGLShaderProgramID OpenGLShaderProgramCreate(OpenGLContext* const openGLContext);
	PXPublic void OpenGLShaderProgramUse(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID);
	PXPublic void OpenGLShaderProgramDelete(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID);

	PXPublic void OpenGLShaderProgramAttach(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID, const OpenGLShaderID shaderID);
	PXPublic void OpenGLShaderProgramLink(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID);
	PXPublic void OpenGLShaderProgramValidate(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID);

	PXPublic GLint OpenGLShaderVariableIDGet(OpenGLContext* const openGLContext, GLuint program, const char* name);
	PXPublic void OpenGLShaderVariableFx1(OpenGLContext* const openGLContext, GLint location, GLfloat v0);
	PXPublic void OpenGLShaderVariableFx1xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value);
	PXPublic void OpenGLShaderVariableIx1(OpenGLContext* const openGLContext, GLint location, GLint v0);
	PXPublic void OpenGLShaderVariableIx1xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value);
	PXPublic void OpenGLShaderVariableFx2(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1);
	PXPublic void OpenGLShaderVariableFx2xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value);
	PXPublic void OpenGLShaderVariableIx2(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1);
	PXPublic void OpenGLShaderVariableIx2xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value);
	PXPublic void OpenGLShaderVariableFx3(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	PXPublic void OpenGLShaderVariableFx3xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value);
	PXPublic void OpenGLShaderVariableIx3(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1, GLint v2);
	PXPublic void OpenGLShaderVariableIx3xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value);
	PXPublic void OpenGLShaderVariableFx4(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	PXPublic void OpenGLShaderVariableFx4xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value);
	PXPublic void OpenGLShaderVariableIx4(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	PXPublic void OpenGLShaderVariableIx4xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value);
	PXPublic void OpenGLShaderVariableMatrix2fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	PXPublic void OpenGLShaderVariableMatrix3fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	PXPublic void OpenGLShaderVariableMatrix4fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	//-------------------------------------------------------------------------

	//---<Buffers>-------------------------------------------------------------
	PXPublic void OpenGLVertexArrayGenerate(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const vaoList);
	PXPublic void OpenGLVertexArrayBind(OpenGLContext* const openGLContext, const unsigned int vaoID);
	PXPublic void OpenGLVertexArrayUnbind(OpenGLContext* const openGLContext);
	PXPublic void OpenGLVertexArrayAttributeDefine
	(
		OpenGLContext* const openGLContext,
		const unsigned int index,
		const unsigned int size,
		const OpenGLDataType datatype,
		const unsigned char normalized,
		const unsigned int stride,
		const PXSize offset
	);
	PXPublic void OpenGLVertexAttributeDivisor(OpenGLContext* const openGLContext, const PXSize index, const PXSize divisor);
	PXPublic void OpenGLVertexArrayEnable(OpenGLContext* const openGLContext, const unsigned int vertexArrayAtributeID);
	PXPublic void OpenGLVertexArrayDisable(OpenGLContext* const openGLContext, const unsigned int vertexArrayAtributeID);

	PXPublic void OpenGLBufferGenerate(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const bufferIDList);
	PXPublic void OpenGLBufferBind(OpenGLContext* const openGLContext, const OpenGLBufferType bufferType, const unsigned int bufferID);
	PXPublic void OpenGLBufferData(OpenGLContext* const openGLContext, const OpenGLBufferType bufferType, const unsigned int size, const void* const data, const OpenGLStoreMode openGLStoreMode);
	PXPublic void OpenGLBufferUnbind(OpenGLContext* const openGLContext, const OpenGLBufferType bufferType);
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	PXPublic void OpenGLFrameBufferCreate(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const framebufferIDList);
	PXPublic void OpenGLRenderBufferStorage(OpenGLContext* const openGLContext, const OpenGLRenderBufferFormat internalformat, const int width, const int height);

	// If we bind to 0, we select the "main window"
	PXPublic void OpenGLFrameBufferBind(OpenGLContext* const openGLContext, const OpenGLFrameBufferMode target, const unsigned int framebufferID);

	PXPublic void OpenGLFrameBufferDestroy(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const framebufferIDList);

	PXPublic void OpenGLRenderBufferCreate(OpenGLContext* const openGLContext, GLsizei n, GLuint* renderbuffers);


	PXPublic void OpenGLRenderBufferBind(OpenGLContext* const openGLContext, const unsigned int renderbuffer);

	PXPublic void OpenGLRenderBufferDelete(OpenGLContext* const openGLContext, GLsizei n, GLuint* renderbuffers);


	PXPublic void OpenGLFrameBufferLinkTexture2D(OpenGLContext* const openGLContext, const OpenGLRenderBufferAttachmentPoint attachment, const OpenGLTextureType textarget, const unsigned int textureID, const int level);
	PXPublic GLuint OpenGLFrameBufferLinkRenderBuffer(OpenGLContext* const openGLContext, const OpenGLRenderBufferAttachmentPoint attachment, const unsigned int renderbuffer);
	//-------------------------------------------------------------------------


	//---<OpenGL v.1.0.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.1.0>------------------------------------------------------
	PXPublic void OpenGLPixelDataRead
	(
		OpenGLContext* const openGLContext,
		const int x,
		const int y,
		const int width,
		const int height,
		OpenGLImageFormat imageFormat,
		OpenGLDataType openGLDataType,
		void* const pixelData
	);
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.2.0>------------------------------------------------------
	//-------------------------------------------------------------------------

	//---<OpenGL v.1.2.1>------------------------------------------------------
    //-------------------------------------------------------------------------

	//---<OpenGL v.1.3.0>------------------------------------------------------
	//-------------------------------------------------------------------------

//---<OpenGL v.1.4.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.1.5.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.2.0.0>------------------------------------------------------

//-------------------------------------------------------------------------

//---<OpenGL v.2.1.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.3.0.0>------------------------------------------------------
PXPublic const char* OpenGLStringGetI(OpenGLContext* const openGLContext, const OpenGLStringName stringName, const unsigned int index);
//-------------------------------------------------------------------------

//---<OpenGL v.3.1.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.3.2.0>------------------------------------------------------
//-------------------------------------------------------------------------


//---<OpenGL v.4.0.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.4.1.0>------------------------------------------------------

//-------------------------------------------------------------------------

//---<OpenGL v.4.2.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.4.3.0>------------------------------------------------------

//-------------------------------------------------------------------------

//---<OpenGL v.4.4.0>------------------------------------------------------
//-------------------------------------------------------------------------

//---<OpenGL v.4.5.0>------------------------------------------------------

//-------------------------------------------------------------------------

//---<OpenGL v.4.6.0>------------------------------------------------------
//-------------------------------------------------------------------------






	/*
	CPublic OpenGLID OpenGLToRenderMode(const PXGraphicRenderMode renderMode);
	CPublic OpenGLID OpenGLToShaderType(const ShaderType shaderType);
	CPublic OpenGLID OpenGLToImageFormat(const ImageDataFormat imageFormat);
	CPublic OpenGLID OpenGLToImageType(const PXGraphicImageType imageType);
	CPublic OpenGLID OpenGLToImageWrap(const PXGraphicImageWrap imageWrap);
	CPublic OpenGLID OpenGLToImageLayout(const PXGraphicImageLayout layout);











	CPublic void OpenGLVertexAttributeArrayDefine(OpenGL* const openGL, const PXSize sizeOfElement, const PXSize listSize, const unsigned int* list);

	CPublic void VertexArrayDefine(unsigned int* vertexArrayID);
	CPublic void VertexDataDefine(unsigned int* vertexID, int size, void* data);
	CPublic void IndexDataDefine(unsigned int* indexID, int size, void* data);
	CPublic void VertexArrayUpdate(int vertexArrayID, int size, void* data);
	*/

#ifdef __cplusplus
}
#endif

#endif
