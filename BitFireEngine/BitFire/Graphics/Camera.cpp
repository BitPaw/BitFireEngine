#include "Camera.h"

Camera::Camera() : Camera(new CameraSettings(1, 1))
{
	
}

Camera::Camera(CameraSettings* settings)
{
	Settings = settings;
	CurrentPosition = new Position();
	
	_view = glm::mat4(1.0f);

	/*
	glm::vec3 camPosition(0.0f, 0.0f, 2.0f);
	glm::vec3 wprldUp(0.0f, 1.0f, 0.0f);
	glm::vec3 camFront(0.0f, 0.0f, -1.0f);
	_view = glm::lookAt(camPosition, camPosition + camFront, wprldUp);*/


	Update();
}

Camera::~Camera()
{
	delete Settings;
	delete CurrentPosition;
}

void Camera::Move(glm::vec3 vector)
{
	_view =  glm::translate(_view,  vector * (-1.0f));
}

void Camera::Update()
{
	switch (Settings->Mode)
	{
	case Orthographic:
		_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, Settings->Far);		
		break;

	case Perspectdive:
		// /*glm::radians()*/Settings->GetVieldOfViewY() Settings->GetAspectRatio()

		_projection = glm::perspective(glm::radians(Settings->FieldOfView), 1.0f, Settings->Near, Settings->Far);
		break;
	}

	_viewProjection = _projection * _view;
}