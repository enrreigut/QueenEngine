#version 330 core

layout(location = 0) in vec4 a_Position;

out vec4 v_Position;

uniform mat4 u_MVP;

void main()
{
	v_Position = a_Position;
	gl_Position = u_MVP * a_Position;
}