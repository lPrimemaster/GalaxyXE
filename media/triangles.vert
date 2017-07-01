#version 450 core

layout( location = 0 ) in vec4 vPosition;

uniform mat4 model, view, project;
//in vec4 coord;

//out vec4 textCoord;

void main()
{
	//texCoord = coord;
    gl_Position = model * vPosition;
}
