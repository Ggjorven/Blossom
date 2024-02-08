#version 460 core

layout(location = 0) out vec4 colour;
layout(location = 0) in vec2 v_TexCoord;

// Define a uniform block
layout(binding = 0) uniform ColourBlock
{
    vec4 u_Colour;
};

layout(binding = 1) uniform  sampler2D u_Tex;

void main()
{
    colour = texture(u_Tex, v_TexCoord);
}
