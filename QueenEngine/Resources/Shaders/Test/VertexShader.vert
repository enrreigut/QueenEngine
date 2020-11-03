#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

uniform float xOffset;

void main()
{
	v_Position = a_Position;
	gl_Position = vec4(a_Position.x * cos(xOffset) - a_Position.y * sin(xOffset), a_Position.y  * cos(xOffset) + a_Position.x * sin(xOffset), a_Position.z, 1.0);
}