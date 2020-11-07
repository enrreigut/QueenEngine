#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

void main()
{
	color = vec4(v_Position.x + 0.5, v_Position.y + 0.5, v_Position.z + 0.5, 1.0);
} 