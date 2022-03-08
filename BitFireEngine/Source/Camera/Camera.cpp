#include "Camera.h"
#include <stdio.h>
#include <cmath>

float BF::Camera::AspectRatioGet()
{
	return (float)Width / (float)Height;
}

void BF::Camera::AspectRatioSet(float width, float height)
{
	Width = width;
	Height = height;

	PerspectiveChange(Perspective);
}

void BF::Camera::PerspectiveChange(CameraPerspective cmeraPerspective)
{
	Perspective = cmeraPerspective;

	switch (Perspective)
	{
		case CameraPerspective::Orthographic:
		{
			float scaling = 0.10;
			float left = -(Width / 2.0f) * scaling;
			float right = (Width / 2.0f) * scaling;
			float bottom = -(Height / 2.0f) * scaling;
			float top = (Height / 2.0f) * scaling;

			MatrixProjection.Orthographic(left, right, bottom, top, Near, Far);
			break;
		}	

		case CameraPerspective::Perspective:
		{
			float aspectRatio = AspectRatioGet();

			MatrixProjection.Perspective(FieldOfView, aspectRatio, Near, Far);
			break;
		}			
	}
}

void BF::Camera::Follow(float deltaTime)
{
	const Vector3<float> cameraPos = MatrixModel.PositionXYZ();

	if (!Target)
	{
		return;
	}

	Vector3<float> targetPos = Target->PositionXYZ();
	Vector3<float> desiredPosition = targetPos + Offset;
	Vector3<float> smoothedPosition = Vector3<float>::Interpolate(cameraPos, desiredPosition, FollowSpeed * deltaTime);

	MatrixModel.MoveTo(smoothedPosition);	
}

BF::Camera::Camera()
{
	_walkSpeed = 0.3;
	_viewSpeed = 2.5;

	FieldOfView = 75;
	Height = 1000;
	Width = 1000;
	Near = 0.01;
	Far = 10000;

	CurrentRotation.Set(0, 0, 0);

	PerspectiveChange(CameraPerspective::Perspective);

	LookAtPosition.Set(1, 0, 0);
	LookAtPosition.Normalize();
}

void BF::Camera::Rotate(float x, float y)
{
	if (x == 0 && y == 0)
	{
		return;
	}

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

	float pitchRAD = Math::DegreeToRadians(CurrentRotation.Y);
	float yawRAD = Math::DegreeToRadians(CurrentRotation.X);
	float rx = cos(pitchRAD) * cos(yawRAD);
	float ry = sin(pitchRAD);
	float rz = cos(pitchRAD) * sin(yawRAD);

	LookAtPosition.Set(rx, ry, rz);
	LookAtPosition.Normalize();
}

void BF::Camera::Move(const float x, const float y, const float z)
{
	Move(Vector3<float>(x, y, z));
}

void BF::Camera::Move(Vector3<float> movement)
{
	Vector3<float> xAxis;
	Vector3<float> yAxis(0, movement.Y, 0);	
	Vector3<float> zAxis;
	Vector3<float> targetedMovement;	
	const Vector3<float> up(0,1,0);
	Vector3<float> lookAtPosition(LookAtPosition.X, LookAtPosition.Y, LookAtPosition.Z);

	xAxis.CrossProduct(lookAtPosition, up);
	xAxis.Normalize();
	xAxis.Multiply(movement.X, 0, movement.X);

	zAxis = lookAtPosition;
	zAxis.Normalize();
	zAxis.Multiply(movement.Z, 0, movement.Z);

	targetedMovement = (xAxis + yAxis + zAxis) *_walkSpeed;

	MatrixModel.Move(targetedMovement);
}

void BF::Camera::Update(float deltaTime)
{
	Vector4<float> currentPositionx4 = MatrixModel.PositionXYZW();
	Vector3<float> currentPosition = Vector3<float>(currentPositionx4.X, currentPositionx4.Y, currentPositionx4.Z);

	float walkSpeedSmoothed = deltaTime * _walkSpeed;
	float viewSpeedSmoothed = deltaTime * _viewSpeed;

	MatrixView.LookAt(currentPosition, currentPosition + LookAtPosition, Vector3<float>(0,1,0));

	//printf("CurrentPosition <%2.2f %2.2f %2.2f>\n", currentPosition.X, currentPosition.Y, currentPosition.Z);

	//Width = Window::Width;
	//Height = Window::Height;

	PerspectiveChange(Perspective);
}