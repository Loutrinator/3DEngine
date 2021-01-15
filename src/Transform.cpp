//
// Created by Marine on 15/01/2021.
//

#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

glm::mat4 Transform::getLocalMatrix() const {
	//                on construit le translate         on ajoute une rotation                          et un scale
	return glm::translate(_position) * glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z) * glm::scale(_scale);
}

glm::vec3 Transform::getPosition() const {
	return _position;
}

void Transform::setPosition(glm::vec3 position) {
	_position = position;
}

glm::vec3 Transform::getRotation() const {
	return _rotation;
}

void Transform::setRotation(glm::vec3 rotation) {
	_rotation = rotation;
}

glm::vec3 Transform::getScale() const {
	return _scale;
}

void Transform::setScale(glm::vec3 scale) {
	_scale = scale;
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
		_position(position), _rotation(rotation), _scale(scale)
{

}
