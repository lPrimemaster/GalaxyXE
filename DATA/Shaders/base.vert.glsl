#version 400 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 uvs;
layout( location = 2 ) in vec3 normal;

//Texture out to fragment shader
//Start using structs in glsl <-- TODO -->
out vec2 fuvs;

out vec3 surfaceNormal;
out vec4 worldPosition;

uniform mat4 ProjView;
uniform mat4 Model;

uniform vec3 lightPosition;

void main()
{
	vec4 worldPos = Model * vPosition;
    gl_Position = ProjView * worldPos;

    fuvs = uvs;
    surfaceNormal = normalize((Model * vec4(normal, 0.0)).xyz);
    worldPosition = worldPos;
}
