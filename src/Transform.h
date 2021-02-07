//
// Created by Marine on 15/01/2021.
//

#ifndef PROJETPHONG_TRANSFORM_H
#define PROJETPHONG_TRANSFORM_H


#include <glm/glm.hpp>

class Transform {
public:
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	glm::mat4 getLocalMatrix() const;
	glm::vec3 getPosition() const;

	void setPosition(glm::vec3 position);

	glm::vec3 getRotation() const;

	void setRotation(glm::vec3 rotation);

	glm::vec3 getScale() const;

	void setScale(glm::vec3 scale);
private :
	glm::vec3	_position;
	glm::vec3	_rotation;
	glm::vec3	_scale;
};


#endif //PROJETPHONG_TRANSFORM_H
