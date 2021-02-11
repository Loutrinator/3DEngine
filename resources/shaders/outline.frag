#version 430 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 camPos;//position de la cam
uniform Material material;
uniform Light light;
uniform sampler2D mainTexture;

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}