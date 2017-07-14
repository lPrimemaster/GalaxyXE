#version 450 core

in vec2 coord;

out vec4 fColor;
uniform sampler2D tex0;

void main()
{
    fColor = vec4(1.0, 0.0, 1.0, 1.0);
}
