//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_CAMERA_H
#define PROJETPHONG_CAMERA_H
#include <glm/glm.hpp>
#include <cmath>

enum CameraMode{
    Free, Orbital
};

class Camera {
public:
	Camera();
	Camera(float fieldOfView,float movingSpeed);

	void setPosition(glm::vec3 position);
	void setTarget(glm::vec3 target);
	void update();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPosition();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();
	void switchCameraMode();
	float FOV;
	float speed;
	float yaw;
	float pitch;
private:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::mat4 _view;
	glm::mat4 _projection;
	float magnitude(glm::vec3 vec);

	CameraMode cameraMode = Free;
	float orbitalRadius = 10;
	float orbitalSpeed = 0.001;
};


#endif //PROJETPHONG_CAMERA_H
