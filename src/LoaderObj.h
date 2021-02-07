#ifndef LOADEROBJ_H
#define LOADEROBJ_H

#include <iostream>
#include "tiny_obj_loader.h"

struct LoadedObj{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> meshes;
    std::vector<tinyobj::material_t> materials;
};

class LoaderObj {
public:
    static LoadedObj Load(const std::string& file);
};

#endif //LOADEROBJ_H
