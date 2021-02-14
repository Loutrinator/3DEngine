#include "LoadedObj.h"

LoadedObj::LoadedObj(Shader *shader, const std::string &path, const std::string &materialPath) {
    loadModel(shader, path, materialPath);
}

void LoadedObj::draw(Camera& camera) {
    for(int i = 0; i < _objects.size(); i++){
        Object* o = _objects[i];
        glm::mat4 model = o->getTransform().getLocalMatrix();
        glm::mat4 MVP = camera.getProjection() * camera.getView() * model;
        Shader& shader = o->getMaterial().getShader();
        shader.setMat4("mvp", MVP);
        shader.setMat4("model", model);

        if(_textures[i] == nullptr)
            glBindTexture(GL_TEXTURE_2D, 0);
        else glBindTexture(GL_TEXTURE_2D, _textures[i]->getId());

        o->draw();
    }
}

void LoadedObj::loadModel(Shader* shader, const std::string& path, const std::string& materialPath) {
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;
    const char* materialPathValue = materialPath.empty() ? NULL : materialPath.c_str();
    bool ret = tinyobj::LoadObj(shapes, materials, error, path.c_str(), materialPathValue);
    if(!error.empty()){
        std::cerr << error;
    }
    if(!ret){
        std::cerr << "Failed to load obj file" << std::endl;
        exit(1);
    }
    std::vector<Material> resultMaterials;
    for(auto& shape : shapes){
        std::vector<float> data;
        std::vector<uint16_t> indices;
        int texCoordsIndex = 0;
        int vertSize = shape.mesh.positions.size();
        auto positions = shape.mesh.positions;
        auto normals = shape.mesh.normals;
        auto texCoords = shape.mesh.texcoords;
        for(int i = 0; i < vertSize; i += 3){
            data.push_back(positions[i]);
            data.push_back(positions[i + 1]);
            data.push_back(positions[i + 2]);
            data.push_back(normals[i]);
            data.push_back(normals[i + 1]);
            data.push_back(normals[i + 2]);
            data.push_back(texCoords[texCoordsIndex++]);
            data.push_back(texCoords[texCoordsIndex++]);
        }
        for(unsigned int index : shape.mesh.indices){
            indices.push_back(index);
        }
        Mesh* m = new Mesh();
        m->setVertices(data.data(), data.size());
        m->setIndices(indices.data(), indices.size());
        tinyobj::material_t currentMat = materials[shape.mesh.material_ids[0]];
        Material* mat = new Material(shader, toVec(currentMat.ambient), toVec(currentMat.diffuse), toVec(currentMat.specular),
                     currentMat.shininess);
        Object* o = new Object(*m, *mat, glm::vec3(0, 1, 0),
                               glm::vec3(0), glm::vec3(1.0f));
        if(!currentMat.diffuse_texname.empty()){
            Texture* texture = new Texture(currentMat.diffuse_texname);
            _textures.push_back(texture);
        } else _textures.push_back(nullptr);
        _materials.push_back(mat);
        _objects.push_back(o);
    }

}
glm::vec3 LoadedObj::toVec(const float * value){
    glm::vec3 result;
    result[0] = value[0];
    result[1] = value[1];
    result[2] = value[2];
    return result;
}
