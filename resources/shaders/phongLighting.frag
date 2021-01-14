#version 430 core
in vec3 fragPos;
in vec3 normals;

layout(location=2) uniform vec3 objectColor;
layout(location=3) uniform vec3 camPos;//position de la cam
layout(location=4) uniform vec3 lightPos;
layout(location=5) uniform vec3 lightColor;
layout(location=6) uniform vec3 ambientColor;
layout(location=7) uniform float ambientStrength;
layout(location=9) uniform float specularStrength;

out vec4 fragColor;

void main()
{
    //AMBIENT

    vec3 ambient = ambientStrength * ambientColor;

    //DIFFUSE

    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normals, lightDir), 0.0);
    vec3 diffuse = diff * objectColor;

    //SPECULAR
    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normals);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    //RESULT
    vec3 result = (ambient + diffuse + specular);
fragColor = vec4(result, 1.0);

    // ------ old --------
    //float luminance = (1+dot(normalize(lightPos),normals))*0.5f;
    //fragColor = luminance*vec4(1.0f,0.5f,0.5f,1.0f); //vec4((1+normalize(normals))*0.5f,1.0f);
}