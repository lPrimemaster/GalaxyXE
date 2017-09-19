#version 400 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 uvs;

out vec2 fuvs;

uniform mat4 ProjView;
uniform mat4 Model;

void main()
{
	fuvs = uvs;
    gl_Position = ProjView * Model * vPosition;
}
