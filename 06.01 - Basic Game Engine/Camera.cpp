#include "Camera.h"




void Camera::init()
{
	_near = 0.1;
	_far = 30;
	_projectionWidth = 30;
	_projectionHeight = 30;
	_FOV = 45;
	_cameraPos = glm::vec3(10.0, 10.0, 10.0);
	_cameraFront = glm::vec3(0, 0, 0);
	_cameraUp = glm::vec3(0, 0, 1);

	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 up = glm::vec3(0.0, 0.0, 1.0);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}



Camera::Camera(int screenWidth, int screenHeight)
{
	_aspectRatio = (screenWidth / screenHeight);
}


Camera::~Camera()
{
}
