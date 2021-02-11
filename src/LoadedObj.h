#ifndef LOADEDOBJ_H
#define LOADEDOBJ_H

#include <iostream>
#include <vector>
#include "Shader.h"
#include "tiny_obj_loader.h"
#include "Object.h"
#include "Camera.h"

class LoadedObj {
public:
    LoadedObj(const std::string& path, Material& defaultMat){
        loadModel(path, defaultMat);
    }
    void draw(Camera& camera);
private:
    void loadModel(const std::string& path, Material& defaultMat);
    std::vector<Object*> _objects;
};


#endif //LOADEDOBJ_H
