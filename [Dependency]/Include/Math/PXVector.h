#ifndef PXVectorINCLUDE
#define PXVectorINCLUDE

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXVector2F_
	{
		union
		{
			struct
			{
				float X;
				float Y;
			};

			float Data[2];
		};
	}
	PXVector2F;

	typedef struct PXVector3F_
	{
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;
			};

			float Data[3];
		};
	}
	PXVector3F;

	typedef struct PXVector4F_
	{
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;
				float W;
			};

			float Data[4];
		};
	}
	PXVector4F;

	PXPublic void PXVector2FConstruct(PXVector2F* const vector2F);
	PXPublic void PXVector3FConstruct(PXVector3F* const vector3F);
	PXPublic void PXVector4FConstruct(PXVector4F* const vector4F);

	PXPublic void PXVector2FSet(const PXVector2F* const vector, PXVector2F* const vectorSet, PXVector2F* const vectorResult);
	PXPublic void PXVector2FSetXY(const PXVector2F* const vector, const float x, const float y, PXVector2F* const vectorResult);
	PXPublic void PXVector3FSetXYZ(const PXVector3F* const vector, const float x, const float y, const float z, PXVector3F* const vectorResult);
	PXPublic void PXVector4FSetXYZW(const PXVector4F* const vector, const float x, const float y, const float z, const float w, PXVector4F* const vectorResult);

	PXPublic void PXVector2FAddXY(const PXVector2F* const vector, const float x, const float y, PXVector2F* const vectorResult);
	PXPublic void PXVector3FAdd(const PXVector3F* const vectorA, const PXVector3F* const vectorB, PXVector3F* const vectorResult);
	PXPublic void PXVector3FAddXYZ(const PXVector3F* const vector, const float x, const float y, const float z, PXVector3F* const vectorResult);
	PXPublic void PXVector4FAddXYZW(const PXVector4F* const vector, const float x, const float y, const float z, const float w, PXVector4F* const vectorResult);

	PXPublic void PXVector2FSubstractxY(const float x, const float y);
	PXPublic void PXVector3FSubstract(const PXVector3F* const vectorA, const PXVector3F* const vectorB, PXVector3F* const vectorResult);
	PXPublic void PXVector3FSubstractXYZ(const float x, const float y, const float z);
	PXPublic void PXVector4FSubstractXYZW(const float x, const float y, const float z, const float w);

	PXPublic void PXVector2FMultiplyXY(const PXVector2F* const vector, const float x, const float y, PXVector2F* const vectorResult);
	PXPublic void PXVector3FMultiply(const PXVector3F* const vector, PXVector3F* const vectorResult);
	PXPublic void PXVector3FMultiplyXYZ(const PXVector3F* const vector, const float x, const float y, const float z, PXVector3F* const vectorResult);
	PXPublic void PXVector3FMultiplyS(const PXVector3F* const vector, const float scalar, PXVector3F* const vectorResult);
	PXPublic void PXVector4FMultiplyXYZW(const PXVector4F* const vector, const float x, const float y, const float z, const float w, PXVector4F* const vectorResult);

	PXPublic void PXVector2FDivideXY(const float x, const float y);
	PXPublic void PXVector3FDivide(const PXVector3F* const vectorA, const PXVector3F* const vectorB, PXVector3F* const vectorResult);
	PXPublic void PXVector3FDivideS(const PXVector3F* const vectorA, const float scalar, PXVector3F* const vectorResult);
	PXPublic void PXVector3FDivideXYZ(const float x, const float y, const float z);
	PXPublic void PXVector4FDivideXYZW(const float x, const float y, const float z, const float w);

	PXPublic void PXVector2FNormalizeXY(const float x, const float y);
	PXPublic void PXVector3FNormalize(const PXVector3F* const vector, PXVector3F* const vectorResult);
	PXPublic void PXVector3FNormalizeXYZ(const float x, const float y, const float z);
	PXPublic void PXVector4FNormalizeXYZW(const float x, const float y, const float z, const float w);



	PXPublic void PXVector2FDistanceTo(PXVector2F* const vectorA, PXVector2F* const vectorB);


	PXPublic float PXVector3FLength(const PXVector3F* const vector);


	PXPublic void PXVector2FCrossProductXY(const float x, const float y);
	PXPublic void PXVector3FCrossProductXYZ(const float x, const float y, const float z);
	PXPublic void PXVector3FCrossProduct(const PXVector3F* const vectorA, const PXVector3F* const vectorB, PXVector3F* const vectorResult);
	PXPublic void PXVector4FCrossProductXYZW(const float x, const float y, const float z, const float w);


	// The point between pojnt a and b.
	PXPublic float PXVector2FDotProduct(const PXVector2F* const vectorA, const PXVector2F* const vectorB);
	PXPublic float PXVector2FDotProductXY(const float x, const float y);
	PXPublic float PXVector3FDotProduct(const PXVector3F* const vectorA, const PXVector3F* const vectorB);
	PXPublic float PXVector3FDotProductXYZ(const float x, const float y, const float z);
	PXPublic float PXVector4FDotProductXYZW(const float x, const float y, const float z, const float w);


	PXPublic void PXVector2FRotateXY(const float x, const float y);
	PXPublic void PXVector3FRotateXYZ(const float x, const float y, const float z);
	PXPublic void PXVector4FRotateXYZW(const float x, const float y, const float z, const float w);

	PXPublic void PXVector2FInterpolateXY(const float x, const float y);
	PXPublic void PXVector3FInterpolate(const PXVector3F* const vectorA, const PXVector3F* const vectorB, const float speed, PXVector3F* const vectorResult);
	PXPublic void PXVector3FInterpolateXYZ(const float x, const float y, const float z);
	PXPublic void PXVector4FInterpolateXYZW(const float x, const float y, const float z, const float w);

#ifdef __cplusplus
}
#endif

#endif