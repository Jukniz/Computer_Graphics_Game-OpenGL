#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
private:
	float _aspectRatio;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	float _FOV;
	float _far;
	float _near;
	float _projectionWidth;
	float _projectionHeight;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;

public:
	void init();
	Camera(int screenWidth, int screenHeight);
	~Camera();
};

