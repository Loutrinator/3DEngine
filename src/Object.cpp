//
// Created by Marine on 13/01/2021.
//

#include "Object.h"

void Object::draw() {
	_mesh->bind();
	glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_SHORT, nullptr);
	_mesh->unbind();
}

Object::Object(Mesh* mesh,int indiceSize):
	_mesh(mesh), position(0.0f), rotation(0.0f), scale(0.0f), _indicesSize(indiceSize)
{
}
