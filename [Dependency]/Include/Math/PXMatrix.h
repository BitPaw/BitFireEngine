#ifndef PXMatrixINCLUDE
#define PXMatrixINCLUDE

#include <Format/Type.h>
#include <Math/PXVector.h>

#define XAxisX 0
#define XAxisY 4
#define XAxisZ 8
#define XAxisW 12

#define YAxisX 1
#define YAxisY 5
#define YAxisZ 9
#define YAxisW 13

#define ZAxisX 2
#define ZAxisY 6
#define ZAxisZ 10
#define ZAxisW 14

#define WAxisX 3
#define WAxisY 7
#define WAxisZ 11
#define WAxisW 15

#define ScaleX 0
#define ScaleY 5
#define ScaleZ 10
#define ScaleW 15

#define TransformX 12
#define TransformY 13
#define TransformZ 14
#define TransformW 15

#ifdef __cplusplus
extern "C"
{
#endif

	/*
		+----+----+----+----+
		| XA | YA | ZA | Or |
		+----+----+----+----+
		|  0 |  1 |  2 |  3 |
		|  4 |  5 |  6 |  7 |
		|  8 |  9 | 10 | 11 |
		| 12 | 13 | 14 | 15 |
		+----+----+----+----+
	*/
	typedef struct PXMatrix4x4F_
	{
		union
		{
			struct
			{
				float XX;
				float XY;
				float XZ;
				float XW;
				float YX;
				float YY;
				float YZ;
				float YW;
				float ZX;
				float ZY;
				float ZZ;
				float ZW;
				float WX;
				float WY;
				float WZ;
				float WW;
			};

			float Data[16];

			float DataXY[4][4];
		};
	}
	PXMatrix4x4F;

	PXPublic void PXMatrix4x4FIdentity(PXMatrix4x4F* const matrix4x4F);
	PXPublic void PXMatrix4x4FResetAxisW(PXMatrix4x4F* const matrix4x4F);

	PXPublic void PXMatrix4x4FPosition(const PXMatrix4x4F* const matrix, PXVector3F* const position);
	PXPublic void PXMatrix4x4FMoveTo(PXMatrix4x4F* const matrixInput, const PXVector3F* const position, PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FMultiply(const PXMatrix4x4F* matrixA, const PXMatrix4x4F* matrixB, PXMatrix4x4F* const matrixResult);
	PXPublic void PXMatrix4x4FRotate(const PXMatrix4x4F* matrixA, const float x, const float y, const float z, PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FCopy(const PXMatrix4x4F* const matrixA, const PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FMove3F(const PXMatrix4x4F* const matrixA, const PXVector3F* const vector3F, PXMatrix4x4F* const matrixResult);
	PXPublic void PXMatrix4x4FMoveXY(const PXMatrix4x4F* const matrixA, const float x, const float y, PXMatrix4x4F* const matrixResult);
	PXPublic void PXMatrix4x4FMoveToScaleXY(const PXMatrix4x4F* const matrixA, const float x, const float y, PXMatrix4x4F* const matrixResult);
	PXPublic void PXMatrix4x4FMoveXYZ(const PXMatrix4x4F* const matrixA, const float x, const float y, const float z, PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FScaleBy(const PXMatrix4x4F* const matrixA, const float scalar, PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FScaleSet(const float x, const float y, const float z, PXMatrix4x4F* const matrixResult);

	PXPublic void PXMatrix4x4FScaleGet(const PXMatrix4x4F* const matrixResult, float* const x, float* const y, float* const z);

	PXPublic void PXMatrix4x4FOrthographic(PXMatrix4x4F* const matrix4x4F, const float left, const float right, const float bottom, const float top, const float nearPlane, const float farPlane);
	PXPublic void PXMatrix4x4FPerspective(PXMatrix4x4F* const matrix4x4F, const float fielfOfView, const float aspectRatio, const float nearPlane, const float farPlane);

	PXPublic PXBool PXMatrix4x4FInverse(const PXMatrix4x4F* const matrix4x4FInput, PXMatrix4x4F* const matrix4x4FResult);
	PXPublic void PXMatrix4x4FTranpose(const PXMatrix4x4F* const matrix4x4FInput, PXMatrix4x4F* const matrix4x4FResult);
	PXPublic void PXMatrix4x4FLookAt(const PXMatrix4x4F* const matrix4x4FInput, const PXVector3F* const eye, const PXVector3F* const  center, const PXVector3F* const up, PXMatrix4x4F* const matrix4x4FResult);

	PXPublic void PXMatrix4x4FPrint(const PXMatrix4x4F* const matrix4x4F, char* const buffer);

#ifdef __cplusplus
}
#endif

#endif
