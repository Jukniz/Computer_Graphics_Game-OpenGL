#include "Camera.h"


Camera::Camera(int screenWidth, int screenHeight)
{
	_aspectRatio = (screenWidth / screenHeight);
}


Camera::~Camera()
{
}

void Camera::init()
{
	_near = 0.1;
	_far = 30;
	_projectionWidth = 30;
	_projectionHeight = 30;
	_FOV = 45;
	_cameraPos = glm::vec3(0.0, -5.0, 5.0); //Punto donde esta
	_cameraFront = glm::vec3(0, 0, 0); //Punto donde mira
	_cameraUp = glm::vec3(0, 0, 1);

	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 up = glm::vec3(0.0, 0.0, 1.0);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

void Camera::orthographicProjection()
{ 
	//_projectionHeight = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2, -_projectionHeight / 2, _projectionHeight / 2, _near, _far);
}

void Camera::perspectiveProjection()
{	
	//_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far); (Esto falla!!)
}





glm::mat4 & Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}

glm::mat4 & Camera::getViewMatrix()
{
	return _viewMatrix;
}
