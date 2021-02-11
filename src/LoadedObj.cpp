#include "LoadedObj.h"

void LoadedObj::draw(Camera& camera) {
    for(int i = 0; i < _objects.size(); i++){
        Object* o = _objects[i];
        glm::mat4 model = o->getTransform().getLocalMatrix();
        glm::mat4 MVP = camera.getProjection() * camera.getView() * model;
        Shader& shader = o->getMaterial().getShader();
        shader.setMat4("mvp", MVP);
        shader.setMat4("model", model);
        o->drawArray();
    }
}

void LoadedObj::loadModel(const std::string& path, Material& defaultMat) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &error, path.c_str());
    if(!error.empty()){
        std::cerr << error;
    }
    if(!ret){
        std::cerr << "Failed to load obj file" << std::endl;
        exit(1);
    }
    std::vector<float> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoordsVec;
    for(int shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++){
        tinyobj::shape_t shape = shapes[shapeIndex];
        tinyobj::mesh_t& mesh = shape.mesh;
        vertices.clear();
        normals.clear();
        texCoordsVec.clear();
        for(auto& i : mesh.indices){
            glm::vec3 position = {
                    attrib.vertices[i.vertex_index * 3],
                    attrib.vertices[i.vertex_index * 3 + 1],
                    attrib.vertices[i.vertex_index * 3 + 2]
            };
            glm::vec3 normal = {
                    attrib.normals[i.normal_index * 3],
                    attrib.normals[i.normal_index * 3 + 1],
                    attrib.normals[i.normal_index * 3 + 2]
            };
            glm::vec2 texCoords = {
                    attrib.texcoords[i.texcoord_index * 2],
                    attrib.texcoords[i.texcoord_index * 2 + 1]
            };
            vertices.push_back(position[0]);
            vertices.push_back(position[1]);
            vertices.push_back(position[2]);
            normals.push_back(normal);
            texCoordsVec.push_back(texCoords);
        }
        Mesh* m = new Mesh();
        m->setVertices(vertices.data(), vertices.size());
        //m->setIndices(indices.data(), indices.size());
        Object* o = new Object(*m, defaultMat, glm::vec3(0, 1, 0), glm::vec3(0), glm::vec3(1.0f));
        _objects.push_back(o);
    }

}
