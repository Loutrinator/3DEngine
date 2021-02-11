#ifndef LOADEDOBJ_H
#define LOADEDOBJ_H

#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "tiny_obj_loader.h"

class LoadedObj {
public:
    void setData(const tinyobj::attrib_t &attrib, const std::vector<tinyobj::shape_t> &shapes,
                 const std::vector<tinyobj::material_t> &materials);
    std::vector<Mesh> getMeshes();
    std::vector<Shader> getMaterials();
private:
    std::vector<Mesh> _meshes;
    std::vector<Shader> _shaders;
};

#endif //LOADEDOBJ_H
