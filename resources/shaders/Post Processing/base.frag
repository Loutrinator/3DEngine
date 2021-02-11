#version 430 core

in vec2 uvs;
uniform sampler2D mainTexture;

out vec4 fragColor;

void main()
{
    fragColor = vec4(vec3(texture(mainTexture, uvs)), 1.0);
}