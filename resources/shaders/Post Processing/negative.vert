#version 430 core

layout(location=0) in vec3 in_vertex;
layout(location=2) in vec2 in_uv;

out vec2 uvs;

void main(){
    gl_Position = vec4(in_vertex,1);
    uvs = in_uv;
}