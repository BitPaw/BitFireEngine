#ifndef PXGraphicINCLUDE
#define PXGraphicINCLUDE

#include <Format/Image.h>
#include <Format/Model.h>
#include <Format/Type.h>
#include <OS/Graphic/OpenGL/OpenGL.h>
#include <Math/PXMatrix.h>
#include <Container/LinkedList/PXLinkedList.h>
#include <OS/Thread/PXLock.h>

#define PXShaderNotRegisterd (unsigned int)-1

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXGraphicRenderFilter_
	{
		PXGraphicRenderFilterInvalid,
		PXGraphicRenderFilterNoFilter, // No filter Option, use this for Pixelated Textures.
		PXGraphicRenderFilterBilinear, // Level I Filter
		PXGraphicRenderFilterTrilinear // Level II Filter
	}
	PXGraphicRenderFilter;

	typedef enum PXShaderType_
	{
		PXShaderTypeInvalid,
		PXShaderTypeVertex,     // .vert - a vertex shader
		PXShaderTypeFragment,   // .frag - a fragment shader
		PXShaderTypeTessellationControl,    // .tesc - a tessellation control shader
		PXShaderTypeTessellationEvaluation,     // .tese - a tessellation evaluation shader
		PXShaderTypeGeometry,      // .geom - a geometry shader		
		PXShaderTypeCompute,   // .comp - a compute shader
	}
	PXShaderType;

	typedef enum PXGraphicImageLayout_
	{
		PXGraphicImageLayoutInvalid,

		// Returns the value of the texture element that is nearest to the specified texture coordinates.
		PXGraphicImageLayoutNearest,

		// Returns the weighted average of the four texture elements that are closest to the specified texture coordinates.
		// These can include items wrapped or repeated from other parts of a texture, depending on the values of GL_TEXTURE_WRAP_Sand GL_TEXTURE_WRAP_T, and on the exact mapping.
		PXGraphicImageLayoutLinear,

		//Chooses the mipmap that most closely matches the size of the pixel being texturedand
		//uses the GL_NEAREST criterion(the texture element closest to the specified texture coordinates) to produce a texture value.
		PXGraphicImageLayoutMipMapNearestNearest,

		//Chooses the mipmap that most closely matches the size of the pixel being texturedand
		//uses the GL_LINEAR criterion(a weighted average of the four texture elements that are closest to the specified texture coordinates) to produce a texture value.
		PXGraphicImageLayoutMipMapLinearNearest,

		//Chooses the two mipmaps that most closely match the size of the pixel being texturedand
		//uses the GL_NEAREST criterion(the texture element closest to the specified texture coordinates)
		//to produce a texture value from each mipmap.The final texture value is a weighted average of those two values.
		PXGraphicImageLayoutMipMapNNearestLinear,

		//Chooses the two mipmaps that most closely match the size of the pixel being texturedand
		//uses the GL_LINEAR criterion(a weighted average of the texture elements that are closest to the specified texture coordinates)
		//to produce a texture value from each mipmap.The final texture value is a weighted average of those two values.
		PXGraphicImageLayoutMipMapLinearLinear
	}
	PXGraphicImageLayout;

	typedef enum PXGraphicImageWrap_
	{
		PXGraphicImageWrapInvalid,

		// Images will be used 'as is' and will not be streched whatsoever.
		PXGraphicImageWrapNoModification,

		// Strech
		PXGraphicImageWrapStrechEdges,

		PXGraphicImageWrapStrechEdgesAndMirror,

		// Tiles the image in a gridformat
		PXGraphicImageWrapRepeat,

		// Tiles the image in a gridformat but also flip them every time.
		PXGraphicImageWrapRepeatAndMirror,
	}
	PXGraphicImageWrap;

	typedef enum PXGraphicImageType_
	{
		PXGraphicImageTypeInvalid,

		PXGraphicImageTypeTexture2D,
		PXGraphicImageTypeTexture3D,

		PXGraphicImageTypeTextureCubeContainer,
		PXGraphicImageTypeTextureCubeRight,
		PXGraphicImageTypeTextureCubeLeft,
		PXGraphicImageTypeTextureCubeTop,
		PXGraphicImageTypeTextureCubeDown,
		PXGraphicImageTypeTextureCubeBack,
		PXGraphicImageTypeTextureCubeFront
	}
	PXGraphicImageType;

	typedef enum PXGraphicRenderMode_
	{
		PXGraphicRenderModeInvalid,
		PXGraphicRenderModePoint,
		PXGraphicRenderModeLine,
		PXGraphicRenderModeLineLoop,
		PXGraphicRenderModeLineStrip,
		PXGraphicRenderModeLineStripAdjacency,
		PXGraphicRenderModeLineAdjacency,
		PXGraphicRenderModeTriangle,
		PXGraphicRenderModeTriangleAdjacency,
		PXGraphicRenderModeTriangleFAN,
		PXGraphicRenderModeTriangleStrip,
		PXGraphicRenderModeTriangleStripAdjacency,
		PXGraphicRenderModeWireFrame,
		PXGraphicRenderModeSquare,
		PXGraphicRenderModePatches
	}
	PXGraphicRenderMode;

	typedef struct Shader_
	{
		unsigned int ID;
		PXShaderType Type;
		PXSize ContentSize;
		char* Content;
	}
	Shader;


	PXPublic void PXShaderConstruct(Shader* const shader);

	PXPublic void PXShaderDataSet(Shader* const shader, const PXShaderType type, const char* data, const PXSize size);


	typedef struct ShaderProgram_
	{
		unsigned int ID;
	}
	ShaderProgram;


	typedef struct PXTexture_
	{
		unsigned int ID;

		PXGraphicImageType Type;
		PXGraphicRenderFilter Filter;
		PXGraphicImageLayout LayoutNear;
		PXGraphicImageLayout LayoutFar;
		PXGraphicImageWrap WrapHeight;
		PXGraphicImageWrap WrapWidth;

		Image Image;
	}
	PXTexture;

	PXPublic void PXTextureConstruct(PXTexture* const texture);
	PXPublic void PXTextureDestruct(PXTexture* const texture);

	typedef struct PXTextureCube_
	{
		unsigned int ID;
		Image ImageList[6];
	}
	PXTextureCube;

	typedef struct CSprite_
	{
		unsigned int ID;
		PXTexture* Texture;
	}
	CSprite;



	typedef enum RefreshRateMode_
	{
		PXRefreshRateUnlimited,
		PXRefreshRateVSync,
		PXRefreshRateCustomSync
	}
	RefreshRateMode;

	typedef struct PXGraphicConfig_
	{
		RefreshRateMode WindowRefreshRateMode;
		unsigned int ScreenResolution[2];
		unsigned char FullScreen;
	}
	PXGraphicConfig;


	//typedef struct Renderable_ Renderable; ?

	typedef struct PXRenderableMeshSegment_
	{
		unsigned int NumberOfVertices;
		unsigned int TextureID;
		unsigned int ShaderID;

		PXGraphicRenderMode RenderMode;

		PXBool DoRendering;
	}
	PXRenderableMeshSegment;

	typedef struct PXRenderable_
	{
		PXMatrix4x4F MatrixModel;

		unsigned int VAO;
		unsigned int VBO;
		unsigned int IBO;

		PXSize MeshSegmentListSize;
		PXRenderableMeshSegment* MeshSegmentList;

		PXBool DoRendering;
	}
	PXRenderable;

	PXPublic void PXRenderableConstruct(PXRenderable* const pxRenderable);


	typedef	struct PXSkyBox_
	{
		PXRenderable Renderable;
		PXTextureCube TextureCube;
	}
	PXSkyBox;

	//---<UI Elements>---------------------------------------------------------

	typedef struct PXUIElement_ PXUIElement;

	typedef void (*PXUIOnClick)(PXUIElement* const pxUIElement);
	typedef void (*PXUIOnMouseEnter)(PXUIElement* const pxUIElement);
	typedef void (*PXUIOnMouseLeave)(PXUIElement* const pxUIElement);

	typedef struct PXUIElement_
	{
		PXRenderable Renderable;

		PXBool HasMouseHover;

		PXUIOnClick OnClickCallback;
		PXUIOnMouseEnter OnMouseEnterCallback;
		PXUIOnMouseLeave OnMouseLeaveCallback;
	}
	PXUIElement;

	typedef struct PXUIPanel_
	{
		PXUIElement UIElement;
	}
	PXUIPanel;

	typedef struct PXUIButton_
	{
		PXUIElement UIElement;
		PXFont* TextFont;
	}
	PXUIButton;

	typedef struct PXUIImage_
	{
		PXUIElement UIElement;
	}
	PXUIImage;

	typedef struct PXOSUIText_
	{
		PXUIElement UIElement;
		PXFont* TextFont;
	}
	PXOSUIText;


	typedef struct PXGraphicContext_
	{
		OpenGLContext OpenGLInstance;

		void* AttachedWindow;

		PXLock _resourceLock;

		PXSkyBox* _currentSkyBox;

		//---<Registered Objects>---
		PXLinkedListFixed _renderList; // PXRenderable
		PXLinkedListFixed _textureList; // PXTexture
		//LinkedList<AudioClip*> _audioClipList;

		PXLinkedListFixed _pxModelList;


		PXLinkedListFixed _pxUIElements;


		//LinkedList<Sound*> _soundList;
		PXLinkedListFixed _fontList; // PXFont
		PXLinkedListFixed _shaderProgramList; // ShaderProgram;
		//LinkedList<Dialog*> _dialogList;
		//LinkedList<Level*> _levelList;
		//LinkedList<Collider*> _physicList;
		//--------------------------
	}
	PXGraphicContext;


	// Create
	PXPublic PXActionResult PXGraphicUIPanelRegister(PXGraphicContext* const graphicContext, PXUIPanel* const pxUIPanel);
	PXPublic PXActionResult PXGraphicUIPanelUpdate(PXGraphicContext* const graphicContext, PXUIPanel* const pxUIPanel);
	PXPublic PXActionResult PXGraphicUIPanelUnregister(PXGraphicContext* const graphicContext, PXUIPanel* const pxUIPanel);

	// 
	// Update
	// Destroy

	PXPublic PXActionResult PXGraphicUITextRegister(PXGraphicContext* const graphicContext, PXOSUIText* const pxUIText, const PXSize x, const PXSize y, const PXSize width, const PXSize height, const PXTextUTF8 text);

	PXPublic PXActionResult PXGraphicUIButtonRegister(PXGraphicContext* const graphicContext, PXUIButton* const pxButton, const PXSize x, const PXSize y, const PXSize width, const PXSize height, const PXTextUTF8 text, const PXFont* const pxFont, const ShaderProgram* const shader);
	 
	 
	 
	//-------------------------------------------------------------------------




	PXPublic void PXRenderableMeshSegmentConstruct(PXRenderableMeshSegment* const pxRenderableMeshSegment);






	//---<OpenGL Translate>----------------
	PXPrivate OpenGLDataType PXGraphicDataTypeToOpenGL(const ImageDataFormat imageDataFormat);
	PXPrivate OpenGLImageFormat PXGraphicImageFormatToOpenGL(const ImageDataFormat imageDataFormat);
	PXPrivate OpenGLShaderType PXGraphicShaderFromOpenGL(const PXShaderType shaderType);
	PXPrivate OpenGLTextureType ImageTypeGraphicToOpenGL(const PXGraphicImageType graphicImageType);
	PXPublic OpenGLRenderMode PXGraphicRenderModeToOpenGL(const PXGraphicRenderMode graphicRenderMode);
	//-------------------------------------

	//-------------------------------------
	PXPublic void PXGraphicInstantiate(PXGraphicContext* const graphicContext);
	//-------------------------------------

	//---<Shader>-----------------------------------------------------------------
	PXPublic PXActionResult PXGraphicShaderProgramCreate(PXGraphicContext* const graphicContext);
	PXPublic PXActionResult PXGraphicShaderCompile(PXGraphicContext* const graphicContext);
	PXPublic PXActionResult PXGraphicShaderUse(PXGraphicContext* const graphicContext, const unsigned int shaderID);

	PXPublic PXActionResult PXGraphicShaderProgramLoadGLSLA(PXGraphicContext* const graphicContext, ShaderProgram* const shaderProgram, const PXTextASCII vertexShaderFilePath, const PXTextASCII fragmentShaderFilePath);
	PXPublic PXActionResult PXGraphicShaderProgramLoadGLSLW(PXGraphicContext* const graphicContext, ShaderProgram* const shaderProgram, const PXTextUNICODE vertexShaderFilePath, const PXTextUNICODE fragmentShaderFilePath);
	PXPublic PXActionResult PXGraphicShaderProgramLoadGLSL(PXGraphicContext* const graphicContext, ShaderProgram* const shaderProgram, Shader* const vertexShader, Shader* const fragmentShader);

	PXPublic void PXGraphicShaderUpdateMatrix4x4F(PXGraphicContext* const graphicContext, const unsigned int locationID, const float* const matrix4x4);
	PXPublic unsigned int PXGraphicShaderVariableIDFetch(PXGraphicContext* const graphicContext, const unsigned int shaderID, const char* const name);
	PXPublic void PXGraphicShaderProgramUse(PXGraphicContext* const graphicContext, const unsigned int shaderID);
	//-------------------------------------------------------------------------

	//---<Rendering>-----------------------------------------------------------
	PXPublic PXBool PXGraphicImageBufferSwap(PXGraphicContext* const graphicContext);
	PXPublic PXActionResult PXGraphicRenderElement(PXGraphicContext* const graphicContext, PXGraphicRenderMode renderMode, PXSize start, PXSize amount);
	PXPublic PXActionResult PXGraphicRenderList(PXGraphicContext* const graphicContext, PXGraphicRenderMode renderMode, PXSize start, PXSize amount);
	//-------------------------------------------------------------------------
	

	//---<Texture>----------------------------------------------------------------
	PXPublic PXActionResult PXGraphicTextureScreenShot(PXGraphicContext* const graphicContext, Image* const image);

	PXPublic PXActionResult PXGraphicTextureLoadA(PXGraphicContext* const graphicContext, PXTexture* const texture, const PXTextASCII filePath);
	PXPublic PXActionResult PXGraphicTextureLoadW(PXGraphicContext* const graphicContext, PXTexture* const texture, const PXTextUNICODE filePath);
	PXPublic PXActionResult PXGraphicTextureRegister(PXGraphicContext* const graphicContext, PXTexture* const texture);
	PXPublic PXActionResult PXGraphicTextureRelease(PXGraphicContext* const graphicContext, PXTexture* const texture);
	PXPublic PXActionResult PXGraphicTextureUse(PXGraphicContext* const graphicContext, PXTexture* const texture);

	PXPublic PXActionResult PXGraphicTextureCubeRegister(PXGraphicContext* const graphicContext, PXTextureCube* const textureCube);
	PXPublic PXActionResult PXGraphicTextureCubeRegisterUse(PXGraphicContext* const graphicContext, PXTextureCube* const textureCube);
	PXPublic PXActionResult PXGraphicTextureCubeRelease(PXGraphicContext* const graphicContext, PXTextureCube* const textureCube);
	//-------------------------------------------------------------------------

	//---<Model>---------------------------------------------------------------
	PXPublic PXActionResult PXGraphicSkyboxRegister(PXGraphicContext* const graphicContext, PXSkyBox* const skyBox);
	PXPublic PXActionResult PXGraphicSkyboxRegisterA
	(
		PXGraphicContext* const graphicContext,
		PXSkyBox** skyBox,
		const char* shaderVertex,
		const char* shaderFragment,
		const char* textureRight,
		const char* textureLeft,
		const char* textureTop,
		const char* textureBottom,
		const char* textureBack,
		const char* textureFront
	);
	PXPublic PXActionResult PXGraphicSkyboxUse(PXGraphicContext* const graphicContext, PXSkyBox* const skyBox);
	PXPublic PXActionResult PXGraphicSkyboxRelease(PXGraphicContext* const graphicContext, PXSkyBox* const skyBox);

	PXPublic PXSize PXGraphicModelListSize(const PXGraphicContext* const graphicContext);
	PXPublic PXBool PXGraphicModelListGetFromIndex(const PXGraphicContext* const graphicContext, PXModel** pxModel, const PXSize index);

	PXPublic PXSize PXGraphicRenderableListSize(const PXGraphicContext* const graphicContext);
	PXPublic PXBool PXGraphicRenderableListGetFromIndex(const PXGraphicContext* const graphicContext, PXRenderable** pxRenderable, const PXSize index);

	PXPublic PXActionResult PXGraphicModelCreate(PXGraphicContext* const graphicContext, PXModel** const pxModel);
	PXPublic PXBool PXGraphicModelRegister(PXGraphicContext* const graphicContext, PXModel* const pxModel);
	PXPublic PXActionResult PXGraphicRenderableCreate(PXGraphicContext* const graphicContext, PXRenderable** const pxRenderable);
	PXPublic PXBool PXGraphicRenderableRegister(PXGraphicContext* const graphicContext, PXRenderable* const pxRenderable);


	PXPublic void PXGraphicModelShaderSet(PXGraphicContext* const graphicContext, PXRenderable* const renderable, const ShaderProgram* const shaderProgram);
	//PXPublic PXActionResult PXGraphicModelGenerate(PXGraphicContext* const graphicContext, PXRenderable** const renderable, const PXTextASCII filePath);
	PXPublic PXActionResult PXGraphicModelLoadA(PXGraphicContext* const graphicContext, PXRenderable* const renderable, const PXTextASCII filePath);
	PXPublic PXActionResult PXGraphicModelRegisterFromModel(PXGraphicContext* const graphicContext, PXRenderable* const renderable, const PXModel* const model);
	PXPublic PXActionResult PXGraphicModelRegisterFromData(PXGraphicContext* const graphicContext, PXRenderable* const renderable, const float* vertexData, const PXSize vertexDataSize, const unsigned int* indexList, const PXSize indexListSize);
	//-------------------------------------------------------------------------

	//PXPublic PXActionResult Load(PXModel& model, const wchar_t* filePath, const bool loadAsynchronously = true);
	//PXPublic PXActionResult Load(PXRenderable& renderable, PXModel* model, const wchar_t* filePath, bool loadAsynchronously = true);
	//PXPublic PXActionResult Load(PXRenderable& renderable, const float* vertexData, const PXSize vertexDataSize, const unsigned int* indexList, const PXSize indexListSize);


	//PXPublic PXActionResult Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously = true);
	// 	PXPublic PXActionResult Load(Collider* collider);

	//PXPublic PXActionResult Load(PXFont& font, const wchar_t* filePath, bool loadAsynchronously = true);
	//PXPublic PXActionResult Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath);

	//PXPublic PXActionResult Load(Image& image, const wchar_t* filePath, bool loadAsynchronously = true);

#ifdef __cplusplus
}
#endif

#endif