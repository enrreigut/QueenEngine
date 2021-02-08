#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	TexCoord = a_TexCoord;
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0);
}