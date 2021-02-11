//
// Created by Antoine on 10/02/2021.
//

#include "Light.h"

void Light::setPosition(const glm::vec3 &position) {
    _pos = position;
}

glm::vec3 Light::getPosition() const {
    return _pos;
}

Light::Light(glm::vec3 &position, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular, Shader* shader):
 _pos(position), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shader(shader) {}

void Light::bind() {
    _shader->setVec3("light.position",_pos);
    _shader->setVec3("light.ambient",_ambient);
    _shader->setVec3("light.diffuse",_diffuse);
    _shader->setVec3("light.specular",_specular);
}

void Light::setShader(Shader* shader) {
    _shader = shader;
}