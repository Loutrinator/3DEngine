#ifndef LOADEDOBJ_H
#define LOADEDOBJ_H

#include <iostream>
#include <vector>
#include "Shader.h"
#include "tiny_obj_loader.h"
#include "Object.h"
#include "Camera.h"
#include "Texture.h"

class LoadedObj {
public:
    LoadedObj(Shader* shader, const std::string& path, const std::string& materialPath = "");
    void draw(Camera& camera);
private:
    void loadModel(Shader* shader, const std::string& path, const std::string& materialPath = "");
    static glm::vec3 toVec(const float* value);
    std::vector<Object*> _objects;
    std::vector<Material*> _materials;
    std::vector<Texture*> _textures;
};


#endif //LOADEDOBJ_H
