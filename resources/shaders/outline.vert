#version 430 core

layout(location=0) in vec3 in_vertex;
layout(location=1) in vec3 in_normals;

layout(location=0) uniform mat4 mvp;//model view projection
layout(location=1) uniform mat4 model;//model to world

void main(){
    //mat3(transpose(inverse(model))) * in_normals
    gl_Position = mvp * vec4((in_normals)*0.07f + in_vertex,1.0f);
}