//
// Created by Antoine on 10/02/2021.
//

#include "Material.h"

Material::Material(Shader* shader, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) : _shader(shader) , _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess){}


void Material::bind() {
    _shader->setVec3("material.ambient",_ambient);
    _shader->setVec3("material.diffuse",_diffuse);
    _shader->setVec3("material.specular",_specular);
    _shader->setFloat("material.shininess",_shininess);
}

void Material::setShader(Shader* shader) {
    _shader = shader;
}

Shader &Material::getShader() {
    return *_shader;
}
