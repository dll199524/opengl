#version 330 core
in vec3 outNormal;
in vec3 outFragPos;
in vec2 outTexCoords;
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;   //相机位置
uniform float ambientStrength;  //环境常量因子

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 objectColor = mix(texture(texture1, outTexCoords), texture(texture2, outTexCoords), 0.1);
    vec3 ambient = ambientStrength * lightColor; //环境光

    vec3 normal = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - outFragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;   //漫反射

    float specularStrength = 0.9; //镜面强度
    vec3 viewDir = normalize(viewPos - outFragPos);
    vec3 reflectDir = reflect(-viewDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor; //镜面光

    vec3 result = (ambient + diffuse + specular) * vec3(objectColor);
    FragColor = vec4(result, 1.0);
}