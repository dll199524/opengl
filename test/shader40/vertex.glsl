#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

out vec3 outFragPos;
out vec3 outNormal;
out vec2 outTexCoords;

uniform float factor;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(Position, 1.0f);
    outFragPos = vec3(model * vec4(Position, 1.0));
    //法线矩阵 解决不等比缩放，对法向量产生的影响
    outNormal = mat3(transpose(inverse(model))) * Normal;
    outTexCoords = TexCoords;
}