#include "LoaderObj.h"

LoadedObj LoaderObj::Load(const std::string &file) {
    LoadedObj loadedObj;
    std::string err;
    bool result = tinyobj::LoadObj(&loadedObj.attributes, &loadedObj.meshes, &loadedObj.materials, &err, file.c_str());
    if(!result){
        std::cerr << "Error loading obj file" << std::endl << err;
        exit(-1);
    }
    return loadedObj;
}
