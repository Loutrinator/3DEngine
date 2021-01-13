#version 430 core
in vec3 fragPos;
in vec3 normals;

layout(location=2) uniform vec3 objectColor;
layout(location=3) uniform vec3 camPos;//position de la cam
layout(location=4) uniform vec3 lightPos;
layout(location=5) uniform vec3 lightColor;

out vec4 fragColor;

void main()
{

    //camPos
    vec3 norm = (normalize(normals)+0.5f)*0.5f;
    fragColor = vec4(norm, 1.0);

    //vec3 lightDir = normalize(lightPos - fragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor;
    //vec3 result = diffuse * objectColor;
    //fragColor = vec4(result, 1.0);

    // ------ old --------
    //float luminance = (1+dot(normalize(lightPos),normals))*0.5f;
    //fragColor = luminance*vec4(1.0f,0.5f,0.5f,1.0f); //vec4((1+normalize(normals))*0.5f,1.0f);
}