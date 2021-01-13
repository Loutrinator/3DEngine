//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_OBJECT_H
#define PROJETPHONG_OBJECT_H

#include "Mesh.h"
#include "Shader.h"

class Object {
public:
	Object(const float* vertices, const uint16_t* indices);
	void draw();
	glm::vec3 position;
	Mesh mesh = Mesh();
	int indicesSize;
private:
};


#endif //PROJETPHONG_OBJECT_H
