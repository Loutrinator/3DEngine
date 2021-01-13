//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_CAMERA_H
#define PROJETPHONG_CAMERA_H
#include <glm/glm.hpp>

class Camera {
public:
	Camera();

	void setPosition(glm::vec3 position);
	void setTarget(glm::vec3 target);
	void update();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPosition();
private:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::mat4 _view;
	glm::mat4 _projection;
};


#endif //PROJETPHONG_CAMERA_H
