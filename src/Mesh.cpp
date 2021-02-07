//
// Created by Marine on 12/01/2021.
//

#include "Mesh.h"

Mesh::Mesh() {

	glGenVertexArrays(1, &_vao); //creation du buffer VAO
	glBindVertexArray(_vao); //ca active le VAO

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);//on défini le format du parametre en _position 0
	glEnableVertexAttribArray(0);// on l'active
	glVertexAttribBinding(0, 0);// on va bind les données du vbo sur le buffer 0 à l'indice 0

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));//on défini le format du parametre en _position 1
	glEnableVertexAttribArray(1);// on l'active
	glVertexAttribBinding(1, 0);// on va bind les données du vbo sur le buffer 0 à l'indice 1

	glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat));//on défini le format du parametre en _position 2
	glEnableVertexAttribArray(2);// on l'active
	glVertexAttribBinding(2, 0);// on va bind les données du vbo sur le buffer 0 à l'indice 2

	glBindVertexArray(0); //debind du VAO
}

void Mesh::setVertices(const float *vertices, size_t size) {

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(_vao);
	glBindVertexBuffer(0,_vbo,0,8*sizeof(GLfloat));
	glBindVertexArray(0);

}

void Mesh::setIndices(const uint16_t *indices, size_t size) {

	glGenBuffers(1, &_ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint16_t), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBindVertexArray(0);
	_indicesSize = size;
}

void Mesh::bind() {
	glBindVertexArray(_vao);
}

void Mesh::unbind() {
	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ibo);
	glDeleteVertexArrays(1, &_vao);
}

int Mesh::getIndiceSize() const {
	return _indicesSize;
}
