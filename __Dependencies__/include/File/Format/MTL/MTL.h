#ifndef MTLInclude
#define MTLInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#define MTLNameSize 32u
#define MTLFilePath 60u

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum MTLLineType_
	{
		MTLLineInvalid,
		MTLLineName,
		MTLLineTexture,
		MTLLineWeight,
		MTLLineColorAmbient,
		MTLLineColorDiffuse,
		MTLLineColorSpecular,
		MTLLineEmission,
		MTLLineDissolved,
		MTLLineDensity,
		MTLLineIllumination
	}
	MTLLineType;

	typedef enum IlluminationMode_
	{
		IlluminationNone,
		IlluminationColorAndAmbientDisable = 0,		// [0] Color on and Ambient off
		IlluminationColorAndAmbientEnable = 1,		// [1] Color on and Ambient on	
		IlluminationHighlightEnable = 2,	// [2] Highlight on	
		IlluminationReflectionOnRayTraceEnable = 3,	// [3] Reflection on and Ray trace on	
		IlluminationReflectionOnRayTraceTransparency = 4, 	// [4] Transparency: Glass on, Reflection : Ray trace on	
		IlluminationReflectionOnRayTraceFresnel = 5, 	// [5] Reflection : Fresnel on and Ray trace on	
		IlluminationReflectionOnRayTraceTransparencyFresnel = 6, 	// [6] Transparency : Refraction on, Reflection : Fresnel offand Ray trace on	
		IlluminationReflectionOnRayTraceFullEnable = 7,	// [7] Transparency : Refraction on, Reflection : Fresnel onand Ray trace on	
		IlluminationReflectionEnable = 8, 	// [8] Reflection on and Ray trace off	
		IlluminationTransparencyEnable = 9, 	// [9] Transparency : Glass on, Reflection : Ray trace off	
		IlluminationShadowsEnable = 10 	// [10] Casts shadows onto invisible surfaces
	}
	IlluminationMode;


	typedef struct MTLMaterial_
	{
		char Name[MTLNameSize];
		char TextureFilePath[MTLFilePath];

		// Ranges between 0 and 1000
		float Weight;

		float Ambient[3];
		float Diffuse[3];
		float Specular[3];
		float Emission[3];

		float Dissolved;

		// range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
		float Density;

		IlluminationMode Illumination;
	}
	MTLMaterial;


	typedef struct MTL_
	{
		size_t MaterialListSize;
		MTLMaterial* MaterialList;
	}
	MTL;

	extern void MTLConstruct(MTL* mtl);
	extern void MTLDestruct(MTL* mtl);

	static MTLLineType MTLPeekLine(const void* line);

	extern ActionResult MTLParse(MTL* mtl, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif