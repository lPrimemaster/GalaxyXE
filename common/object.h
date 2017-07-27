#pragma once
#include "../shader.h"
#include "model.h"

#define ENGINE_OBJ_PROGRAM_UNBIND 0x06
#define ENGINE_OBJ_PROGRAM_BIND 0x07

class Object
{
public:
	Object(Model* mesh, Shader* shaders[], const char* Uniforms);
	void render();
	void bind();
	void modelTransform(GLfloat scale, vmath::vec3 rotateDegrees, vmath::vec3 translate);
	void update();
	GLuint & getProgram();
	~Object();
private:
	Model* mesh;
	enum EBO { indices, numEBOs };
	enum VBO { vertices, uvs, numVBOs };
	enum VAO { triangles, numVAOs };
	enum UNI { model, scale, numUNIs };
	enum TEX { tex0, numTEXs };

	GLuint uniforms[numUNIs];

	GLuint EBO[numEBOs];
	GLuint VBO[numVBOs];
	GLuint VAO[numVAOs];

	Shader* vertexShader;
	Shader* fragmentShader;
	Program* program;

	GLuint textures[numTEXs];

	vmath::mat4 modelMatrix;

	//Helper functions
	int getArrayPos(std::vector<unsigned int> vector, unsigned int value);
};

