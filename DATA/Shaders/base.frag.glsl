#version 450 core

in vec2 fuvs;

out vec4 fColor;
uniform sampler2D sampler;

void main()
{
    fColor = texture(sampler, fuvs);
}
