#version 450 core

in vec2 coord;

out vec4 fColor;
uniform sampler2D tex1;

void main()
{
    fColor = texture(tex1, coord);
}