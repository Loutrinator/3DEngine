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

in vec3 fragPos;
in vec3 normals;
in vec2 uvs;

uniform vec3 camPos;//position de la cam
uniform Material material;
uniform Light light;
uniform sampler2D mainTexture;

out vec4 fragColor;

void main()
{
    vec3 normal = normalize(normals);
    //AMBIENT
    vec3 ambient = material.ambient * light.ambient;

    //DIFFUSE
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * light.diffuse * vec3(texture(mainTexture, uvs));

    //SPECULAR
    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * light.specular;
    //RESULT
    vec3 result = (ambient + diffuse + specular);
    fragColor = vec4(result, 1.0);

}