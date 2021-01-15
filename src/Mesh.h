
//
// Created by Marine on 12/01/2021.
//

#ifndef PROJETPHONG_MESH_H
#define PROJETPHONG_MESH_H


#include <cstdint>
#include <glad/glad.h>

class Mesh {
public:
	Mesh();
	~Mesh();
	void setVertices(const float* vertices, size_t size);
	void setIndices(const uint16_t* indices, size_t size);
	void bind();
	void unbind();
private:
	GLuint _vao;//definir setup avec les attributs du shader (quel buffer etc)
	GLuint _vbo;//notre buffer qui contient les vertices
	GLuint _ibo;//notre buffer qui contient les indices du vbo

};


#endif //PROJETPHONG_MESH_H
