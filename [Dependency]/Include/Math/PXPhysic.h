#ifndef PXPhysicINCLUDE
#define PXPhysicINCLUDE

#include <Format/Type.h>
#include <Math/PXVector.h>
#include <Math/PXMatrix.h>

#ifdef __cplusplus
extern "C"
{ 
#endif

	typedef struct PXPhysicProperties_
	{
		PXMatrix4x4F MatrixModel;
		PXVector3F Velocity;
		PXVector3F Force;
		float Mass;
		float Friction;
		// Frriction static / dynamic
		// elastistity / boncyness

		PXBool EnablePhysics;
		PXBool EnableGravity;
		PXBool IsSolid;
	}
	PXPhysicProperties;

    PXPublic void PXPhysicGravityApply(PXPhysicProperties* const physicProperties, const PXVector3F* const gravityDircetion, const float gravityForce, const float deltaTime);

    
#ifdef __cplusplus
}
#endif

#endif