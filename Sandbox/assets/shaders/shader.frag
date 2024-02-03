#version 460 core

layout(location = 0) out vec4 colour;

layout(location = 0) in vec3 v_Colour;

void main()
{
	colour = vec4(v_Colour, 1.0);
}