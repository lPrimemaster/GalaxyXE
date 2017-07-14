#version 450 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 texCoord;

uniform mat4 model, view, project;

out vec2 coord;

void main()
{
	coord = texCoord;
    gl_Position = model * vPosition;
}
