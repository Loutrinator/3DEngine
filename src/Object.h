//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_OBJECT_H
#define PROJETPHONG_OBJECT_H

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

class Object {
public:
	Object(Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void draw();
	Transform getTransform();
private:
	Mesh* _mesh;
	Transform _transform;
};


#endif //PROJETPHONG_OBJECT_H
