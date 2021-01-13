//
// Created by Marine on 13/01/2021.
//

#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera() {
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_target = glm::vec3(0.0f, 0.0f, 0.0f);
}
void Camera::update() {

	_forward = glm::normalize(_position - _target);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(up, _forward));
	_up = glm::cross(_forward, _right);
	//_view = glm::lookAt(_position,_target,up);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = viewport[2] / (float) viewport[3];

	_projection = glm::perspective(glm::radians(60.0f), ratio, 0.01f, 100.0f);
	const float radius = 20.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	_position = glm::vec3(camX,_position.y,camZ);
	_view = glm::lookAt(_position, _target, glm::vec3(0.0, 1.0, 0.0));
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
}

void Camera::setTarget(glm::vec3 target) {
	_target = target;
}

glm::mat4 Camera::getView() {
	return _view;
}
glm::mat4 Camera::getProjection() {
	return _projection;
}

glm::vec3 Camera::getPosition() {
	return _position;
}
