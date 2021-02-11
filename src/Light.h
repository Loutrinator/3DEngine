//
// Created by Antoine on 10/02/2021.
//

#ifndef LIGHT_H
#define LIGHT_H


#include <glm/vec3.hpp>
#include "Shader.h"

class Light {
public:
    Light(glm::vec3& position, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular, Shader* shader);
    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition() const;
    void setShader(Shader* shader);
    void bind();
private:
    glm::vec3 _pos;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
    Shader* _shader;
};


#endif //LIGHT_H
