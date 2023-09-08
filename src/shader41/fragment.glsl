#version 33o core
in vec3 outFragPos;
in vec3 outNormal;
in vec2 outTexCoords;

out vec4 FragColor;

uniform vec3 lightPos;
unifrom vec3 lightColor;
unifrom vec3 viewPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

//定义材质结构体
struct Material 
{
    vec3 ambient;   //环境光
    vec3 diffuse;   //漫反射
    vec3 
    
}