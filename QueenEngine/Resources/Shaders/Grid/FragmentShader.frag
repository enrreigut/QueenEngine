#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 0.4);
} 