#ifndef PXCameraINCLUDE
#define PXCameraINCLUDE

#include <Format/Type.h>
#include <Math/PXMatrix.h>
#include <Math/PXVector.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXCameraPerspective_
	{
		PXCameraPerspective2D,
		PXCameraPerspective3D // Perspective
	}
	PXCameraPerspective;

	typedef struct PXCamera_
	{
		PXMatrix4x4F MatrixModel;
		PXMatrix4x4F MatrixView;
		PXMatrix4x4F MatrixProjection;

		float WalkSpeed;
		float ViewSpeed;

		PXVector3F LookAtPosition;
		PXVector3F CurrentRotation;		

		//---<Follow>---
		PXVector3F Offset;
		PXMatrix4x4F* Target;
		float FollowSpeed; // Ranges from 0 to 1 .. FollowSpeed; = 0.98f

		PXCameraPerspective Perspective;

		float FieldOfView;
		PXSize Height;
		PXSize Width;
		float Near;
		float Far;	
	}
	PXCamera;

	PXPublic void PXCameraConstruct(PXCamera* const camera);
	PXPublic void PXCameraDestruct(PXCamera* const camera);


	//-----------
	PXPublic float PXCameraAspectRatio(const PXCamera* const camera);
	PXPublic void PXCameraAspectRatioChange(PXCamera* const camera, const PXSize width, const PXSize height);

	PXPublic void PXCameraViewChange(PXCamera* const camera, const PXCameraPerspective cameraPerspective);
	PXPublic void PXCameraViewChangeToOrthographic(PXCamera* const camera, const PXSize width, const PXSize height, const float nearPlane, const float farPlane);
	PXPublic void PXCameraViewChangeToPerspective(PXCamera* const camera, const float fieldOfView, const float aspectRatio, const float nearPlane, const float farPlane);
	//-----------

	//---<Transform>-----------------------------------------------------------
	PXPublic void PXCameraRotate(PXCamera* const camera, const PXVector3F* const vector3F);
	PXPublic void PXCameraRotateXYZ(PXCamera* const camera, const float x, const float y, const float z);

	PXPublic void PXCameraMove(PXCamera* const camera, const PXVector3F* const vector3F);
	PXPublic void PXCameraMoveXYZ(PXCamera* const camera, const float x, const float y, const float z);

	PXPublic void PXCameraFollow(PXCamera* const camera, const float deltaTime);
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	PXPublic void PXCameraUpdate(PXCamera* const camera, const float deltaTime);
	//-------------------------------------------------------------------------




#ifdef __cplusplus
}
#endif

#endif