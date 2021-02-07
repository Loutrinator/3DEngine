//
// Created by Marine on 13/01/2021.
//

#include "Object.h"

Object::Object(Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
		_mesh(mesh), _transform(position, rotation, scale)
{
}

void Object::draw() {
	_mesh->bind();
	glDrawElements(GL_TRIANGLES, _mesh->getIndiceSize(), GL_UNSIGNED_SHORT, nullptr);
	_mesh->unbind();
}

Transform Object::getTransform() {
	return _transform;
}
