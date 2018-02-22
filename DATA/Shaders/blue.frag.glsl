#version 450 core

in vec2 fuvs;

out vec4 fColor;
uniform sampler2D tex;

void main()
{
    fColor = vec4(0.5, 0.2, 0.3, 1.0);
}
