#include "LoadedObj.h"

void LoadedObj::setData(const tinyobj::attrib_t &attrib, const std::vector<tinyobj::shape_t> &shapesP,
                        const std::vector<tinyobj::material_t> &materialsP) {
    tinyobj::attrib_t attributes = attrib;
    std::vector<tinyobj::shape_t> shapes = shapesP;
    //std::vector<tinyobj::material_t> materials = materialsP;

    _meshes = std::vector<Mesh>();
    _shaders = std::vector<Shader>();
    for(const auto& shape : shapes){
        std::cout << "Shape : " << shape.name << std::endl;

        tinyobj::mesh_t mesh = shape.mesh;
        int numFace = mesh.num_face_vertices.size();

        int indOffset = 0;
        std::vector<uint16_t> vertexIndices;
        std::vector<float> vertices;
        for(int i = 0; i < numFace; i++){
            int numVertices = mesh.num_face_vertices[i];
            for(int j = 0; j < numVertices; j++){
                tinyobj::index_t index = mesh.indices[j + indOffset];
                float vx = attributes.vertices[3 * index.vertex_index];
                float vy = attributes.vertices[3 * index.vertex_index + 1];
                float vz = attributes.vertices[3 * index.vertex_index + 2];
                vertices.insert(vertices.end(), vx);
                //vertices.insert(vertices.end(), vy);
                //vertices.insert(vertices.end(), vz);
                vertexIndices.insert(vertexIndices.end(), index.vertex_index);
            }
            indOffset += numVertices;
        }
        Mesh m;
        m.setIndices(vertexIndices.data(), vertexIndices.size());
        m.setVertices(vertices.data(), vertices.size());
        _meshes.push_back(m);
        _shaders.emplace_back(Shader("phongLighting"));
        std::cout << "Mesh indices, vertices : " << vertices.size() << ", " << vertexIndices.size() << std::endl;
    }
    std::cout << "Loaded meshes : " << _meshes.size() << std::endl;
}

std::vector<Mesh> LoadedObj::getMeshes() {
    return _meshes;
}

std::vector<Shader> LoadedObj::getMaterials() {
    return _shaders;
}
