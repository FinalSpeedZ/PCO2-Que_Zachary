#include "PerspectiveCamera.hpp"

using namespace cameras;

PerspectiveCamera::PerspectiveCamera(float FOV, float window_height, float window_width, float near, float far,
	glm::vec3 pos, glm::vec3 worldUp, glm::vec3 center)
	: MyCamera(pos, worldUp, center)
{
	// Create the ProjMatrix
	this->projMatrix = glm::perspective(
		glm::radians(FOV),
		(float)window_height / (float)window_width,
		near,
		far
	);
}