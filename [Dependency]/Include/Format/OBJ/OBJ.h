#ifndef OBJInclude
#define OBJInclude

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>
#include <File/PXDataStream.h>

#include <Format/MTL/MTL.h>
#include <Format/Model.h>

#define OBJNameSize 64u
#define OBJElementNameLength 50u
#define OBJDebug 1

#ifdef __cplusplus
extern "C"
{
#endif	

	typedef enum OBJLineType_
	{
		OBJLineInvalid,
		OBJLineNone,
		OBJLineComment,
		OBJLineMaterialLibraryInclude,
		OBJLineMaterialLibraryUse,
		OBJLineObjectName,
		OBJLineObjectGroup,
		OBJLineVertexGeometric,
		OBJLineVertexTexture,
		OBJLineVertexNormal,
		OBJLineVertexParameter,
		OBJLineSmoothShading,
		OBJLineFaceElement,

		OBJEmbeddedMTL
	}
	OBJLineType;

	typedef struct OBJElementMaterialInfo_
	{
		PXSize MaterialIndex;
		PXSize Size; // Size of buffer to use given material		
	}
	OBJElementMaterialInfo;

	typedef struct OBJElement_
	{
		char Name[OBJElementNameLength];
		float Smoothing;

		OBJElementMaterialInfo* MaterialInfo;
		PXSize MaterialInfoSize;

		PXSize VertexPositionListSize;
		float* VertexPositionList; 	// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.

		PXSize TextureCoordinateListSize;
		float* TextureCoordinateList; 	// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.

		PXSize VertexNormalPositionListSize;
		float* VertexNormalPositionList; 	// List of vertex normals in (x,y,z) form; normals might not be unit vectors.

		PXSize VertexParameterListSize;
		float* VertexParameterList; // Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.

		PXSize FaceElementListSize;
		unsigned int* FaceElementList; // Polygonal face element.	
	}
	OBJElement;

	extern void OBJElementConstruct(OBJElement* objElement);
	extern void OBJElementDestruct(OBJElement* objElement);

	// [.OBJ] Wavefront - 3D model format
	typedef struct OBJ_
	{
		wchar_t Name[OBJNameSize];
		unsigned char VertexStructureSize;

		PXSize MaterialFileListSize;
		MTL* MaterialFileList;

		PXSize ElementListSize;
		OBJElement* ElementList;
	}
	OBJ;

	PXPublic void OBJConstruct(OBJ* const obj);
	PXPublic void OBJDestruct(OBJ* const obj);

	PXPrivate OBJLineType OBJPeekLine(const void* line, const PXSize size);

	PXPublic PXActionResult OBJFileCompile(PXDataStream* const inputStream, PXDataStream* const outputStream);

	PXPublic PXActionResult OBJParseToModel(PXDataStream* const inputStream, PXModel* const model);

#ifdef __cplusplus
}
#endif

#endif