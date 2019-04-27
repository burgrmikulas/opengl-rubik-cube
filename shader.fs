#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
// in vec2 texCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
// uniform sampler2D ourTexture;
// uniform vec3 lightPos;

void main()
{
   // Ambient light
   vec3 lightColor = vec3(1.0);
   float ambientStrength = 1.0;
   vec3 ambient = ambientStrength * lightColor;
   // Diffuse light
   vec3 lightPos = vec3(0.2, 0.2, 5.0);
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;
   // Specular light
   // FIX: Camera position now not updating properly
   float specularStrength = 0.5;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightColor;
   vec3 result = (ambient + diffuse + specular) * vertexColor;
   FragColor = vec4(result, 1.0);
}