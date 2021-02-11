#ifndef LOADEDOBJ_H
#define LOADEDOBJ_H

#include <iostream>
#include <vector>
#include "Shader.h"
#include "tiny_obj_loader.h"
#include "Mesh.h"


class LoadedObj {
public:
    explicit LoadedObj(const std::string& path){
        loadModel(path);
    }
    void draw();
private:
    void loadModel(const std::string& path);
    std::vector<Mesh*> _meshes;
};


#endif //LOADEDOBJ_H
