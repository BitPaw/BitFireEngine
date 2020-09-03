#include "Camera.h"

Camera::Camera() : Camera(new CameraSettings(1, 1))
{
	
}

Camera::Camera(CameraSettings* settings)
{
	Settings = settings;
	CurrentPosition = new Position();

	_projection = glm::perspective(glm::radians(Settings->GetVieldOfViewY()), Settings->GetAspectRatio(), Settings->Near, Settings->Far);
	_view = glm::mat4(1.0f);

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
	_viewProjection = _projection * _view;
}