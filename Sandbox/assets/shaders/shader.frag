#version 460 core

layout(location = 0) out vec4 colour;
layout(location = 0) in vec3 v_Colour;

// Define a uniform block
layout(binding = 0) uniform ColourBlock
{
    vec4 u_Colour;
};

void main()
{
    colour = u_Colour; // Use the uniform from the block
}
