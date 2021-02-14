//
// Created by Marine on 13/01/2021.
//

#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Engine.h"



Camera::Camera() {

}
Camera::Camera(float fieldOfView,float movingSpeed) {
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_target = glm::vec3(0.0f, 0.0f, 0.0f);
	FOV = fieldOfView;
	speed = movingSpeed;
	yaw = 0;
	pitch = 0;
}
void Camera::update() {

	speed = 2.5f * Engine::instance->deltaTime;

	_forward = glm::normalize(_position - _target);

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	_forward = glm::normalize(direction);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(up, _forward));
	_up = glm::cross(_forward, _right);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = viewport[2] / (float) viewport[3];
	//std::cout << _position.x << " " << _position.y << " " << _position.z << "\n";
	_projection = glm::perspective(glm::radians(FOV), ratio, 0.01f, 100.0f);
	_view = glm::lookAt(_position, _position + _forward, _up);
	

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

void Camera::moveLeft() {
    if(cameraMode == Free){
	    _position -= speed * _right;
    }
}

void Camera::moveRight() {
    if(cameraMode == Free) {
        _position += speed * _right;
    }
}

void Camera::moveForward() {
    if(cameraMode == Free){
	    _position += speed * _forward;
    }
}
void Camera::moveBackward() {
    if(cameraMode == Free){
	    _position -= speed * _forward;
    }
}
void Camera::moveUp() {
    if(cameraMode == Free){
	    _position += speed * _up;
    } else {
        //float a = orbitalRadius /
        _position += orbitalSpeed * sin(orbitalRadius * _up);
    }
}
void Camera::moveDown() {
    if(cameraMode == Free){
	_position -= speed * _up;
    } else {

    }
}

void Camera::switchCameraMode() {
    if(cameraMode == Free)
        cameraMode = Orbital;
    else cameraMode = Free;
    std::string cameraModeStr = cameraMode == Free ? "Free" : "Orbital";
    std::cout << "Camera mode : " << cameraModeStr << std::endl;
}

float Camera::magnitude(glm::vec3 vec) {
    return sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}

