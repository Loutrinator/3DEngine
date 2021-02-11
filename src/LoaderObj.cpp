#include "LoaderObj.h"

LoadedObj LoaderObj::Load(const std::string &file) {
    LoadedObj loadedObj;
    std::string err;
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    bool result = tinyobj::LoadObj(&attributes, &shapes, &materials, &err, file.c_str());
    if(!err.empty()){
        std::cerr << err;
    }
    if(!result){
        std::cerr << "Failed loading obj file" << std::endl;
        exit(-1);
    }
    loadedObj.setData(attributes, shapes, materials);
    return loadedObj;
}
