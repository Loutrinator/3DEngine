//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_OBJECT_H
#define PROJETPHONG_OBJECT_H

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"

class Object {
public:
	Object(Mesh& mesh, Material& material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void draw();
	void drawArray();
	Transform& getTransform();
	void setMaterial(Material& material);
	Material& getMaterial();
private:
    Mesh& _mesh;
    Material& _material;
	Transform _transform;
};


#endif //PROJETPHONG_OBJECT_H
