#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;

out outFragPos;
out outNormal;
out outTexCoords;

uniform mat4 view;
unifrom mat4 model;
unifrom mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(Position, 1.0f);
    outFragPos = vec3(model * vec4(Position, 1.0f));
    outNormal = mat3(transpose(inverse(model))) * Normal;
    outTexCoords = TexCoords;
}