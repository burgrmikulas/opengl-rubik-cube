#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
// layout (location = 2) in vec2 aTexCoord;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
// out vec2 texCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  FragPos = vec3(model * vec4(aPos, 1.0));
  vertexColor = vec3(0.0, 0.5, 0.8);
  // texCoord = aTexCoord;
  Normal = mat3(transpose(inverse(model))) * aNormal;
}