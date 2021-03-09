#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normals;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normals;
out vec3 LightPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform vec3 gLightPos;

void main()
{
	TexCoord = a_TexCoord;
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0);
	
	FragPos = vec3(u_View * u_Model * vec4(a_Position, 1.0));
	Normals = mat3(transpose(inverse(u_View * u_Model))) * a_Normals;
	LightPos = vec3(u_View * vec4(gLightPos, 1.0));
}