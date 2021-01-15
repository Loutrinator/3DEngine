//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_OBJECT_H
#define PROJETPHONG_OBJECT_H

#include "Mesh.h"
#include "Shader.h"

class Object {
public:
	Object(Mesh* mesh, int indiceSize);
	void draw();
private:
	Mesh* _mesh;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	int _indicesSize;
};


#endif //PROJETPHONG_OBJECT_H
