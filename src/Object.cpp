//
// Created by Marine on 13/01/2021.
//

#include "Object.h"

Object::Object(const float* vertices,const  uint16_t* indices) {
	mesh = Mesh();
	mesh.setVertices(vertices, sizeof(vertices) / sizeof(float));
	indicesSize = sizeof(indices) / sizeof(uint16_t);
	mesh.setIndices(indices, indicesSize);
}

void Object::draw() {
	mesh.bind();
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_SHORT, nullptr);
	mesh.unbind();
}
