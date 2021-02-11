//
// Created by Antoine on 10/02/2021.
//

#pragma once


#include <glm/vec3.hpp>
#include "Shader.h"

class Material {
public:
    Material(Shader* shader, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);

    void bind();
    void setShader(Shader* shader);
private:
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
    float _shininess;
    Shader* _shader;
    /*
    blueMaterial.setVec3("camPos",mainCamera.getPosition());
    blueMaterial.setMat4("mvp",planeMvp);
    blueMaterial.setMat4("model",planeModel);
    blueMaterial.setVec3("light.position",lightPos);
    blueMaterial.setVec3("light.ambient",lightAmbient);
    blueMaterial.setVec3("light.diffuse",lightDiffuse);
    blueMaterial.setVec3("light.specular",lightSpecular);*/
};
