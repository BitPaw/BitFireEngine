#include "Camera.h"
#include <stdio.h>

float BF::Camera::GetAspectRatio()
{
	return Width / Height;
}

void BF::Camera::PerspectiveChange(CameraPerspective cmeraPerspective)
{
	Perspective = cmeraPerspective;

	switch (Perspective)
	{
		case CameraPerspective::Orthographic:
			MatrixProjection.Orthographic(-10.0f, 10.0f, -10.0f, 10.0f, Near, Far);
			break;

		case CameraPerspective::Perspective:
			MatrixProjection.Perspective(FieldOfView, GetAspectRatio(), Near, Far);
			break;
	}
}

BF::Camera::Camera()
{
	_walkSpeed = 0.3;
	_viewSpeed = 2.5;

	FieldOfView = 90;
	Height = 1000;
	Width = 1000;
	Near = 0.01;
	Far = 10000;

	CurrentRotation.Set(0, 0, 0);

	PerspectiveChange(CameraPerspective::Perspective);
}

void BF::Camera::Rotate(float x, float y)
{
	const float maxValue = 85.0f;
	const float minValue = -85.0f;
	float movementSpeed = _viewSpeed;

	CurrentRotation.X -= x * movementSpeed;
	CurrentRotation.Y += y * movementSpeed;

	// Cap
	if (CurrentRotation.Y > maxValue)
	{
		CurrentRotation.Y = maxValue;
	}

	if (CurrentRotation.Y < minValue)
	{
		CurrentRotation.Y = minValue;
	}

	float pitchRAD = glm::radians(CurrentRotation.Y);
	float yawRAD = glm::radians(CurrentRotation.X);


	float rx = cos(pitchRAD) * cos(yawRAD);
	float ry = sin(pitchRAD);
	float rz = cos(pitchRAD) * sin(yawRAD);

	LookAtPosition.Set(rx, ry, rz);
	LookAtPosition.Normalize();
}

void BF::Camera::Move(Vector3<float> movement)
{
	float xAxisMovement = movement.Data[0];
	float yAxisMovement = movement.Data[1];
	float zAxisMovement = movement.Data[2];
	Vector3<float> yAxis(0, yAxisMovement, 0);
	Vector3<float> xAxis;
	Vector3<float> zAxis(zAxisMovement, 0, zAxisMovement);
	Vector3<float> targetedMovement;	

	xAxis.CrossProduct(LookAtPosition, Vector3<float>(0, 1, 0));
	xAxis.Multiply(xAxisMovement, 0, xAxisMovement);
	xAxis.Normalize();

	zAxis *= LookAtPosition;

	targetedMovement = (xAxis + yAxis + zAxis) *_walkSpeed;

	MatrixModel.Move(targetedMovement);
}

void BF::Camera::Update(float deltaTime)
{
	Vector4<float> currentPositionx4 = MatrixModel.CurrentPosition();
	Vector3<float> currentPosition = Vector3<float>(currentPositionx4.Date[0], currentPositionx4.Date[1], currentPositionx4.Date[2]);

	float walkSpeedSmoothed = deltaTime * _walkSpeed;
	float viewSpeedSmoothed = deltaTime * _viewSpeed;

	MatrixView.LookAt(currentPosition, currentPosition + LookAtPosition, Vector3<float>(0,1,0));

	Vector3<float> gravity = Vector3<float>(0.f, -0.918f, 0.f);

	MatrixModel.Motion(Force, Velocity, 1, gravity, deltaTime);

	//printf("CurrentPosition <%2.2f %2.2f %2.2f>\n", currentPosition.Data[0], currentPosition.Data[1], currentPosition.Data[2]);
}