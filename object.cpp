#include "object.h"

Object::Object(Model* mesh, Shader* shaders[], const char* Uniforms)
{
	//Reference the mesh model for the entity
	this->mesh = mesh;

	if (shaders != NULL)
	{
		//Get the shaders and reference them from an array
		for (unsigned int i = 0; i < 2; i++)
		{
			switch (shaders[i]->getType())
			{
			case GL_VERTEX_SHADER:
				this->vertexShader = shaders[i];
				break;
			case GL_FRAGMENT_SHADER:
				this->fragmentShader = shaders[i];
				break;
			default:
				cout << "Shader type not found!" << endl;
				break;
			}
		}

		//Initialize the program
		program = new Program();
		this->vertexShader->link(*program);
		this->fragmentShader->link(*program);
		program->build();
		program->use();

		//Uniform Loader
		//Later update to use a Uniform Block
		if (Uniforms != NULL)
		{
			int li = 0;
			int bi = 0;
			char buffer[10][20];
			for (unsigned int i = 0; i < strlen(Uniforms) + 1; i++)
			{
				if (Uniforms[i] == ' ' || Uniforms[i] == '\0')
				{
					int bz = 0;
					for (unsigned int z = li; z < i; z++)
					{
						buffer[bi][bz++] = Uniforms[z];
					}
					buffer[bi][bz] = '\0';
					bi++;
					li = i + 1;
				}
			}
			for (int i = 0; i < bi; i++)
			{
				uniforms[i] = glGetUniformLocation(this->program->getProgram(), buffer[i]);
				if (uniforms[i] == -1)
				{
					cout << "[Engine] ERROR: Uniform [" << buffer[i] << "] does not exist in the shader." << endl;
				}
#if DEBUG
				cout << "[Engine] Uniform name at [i = " << i << "]: " << buffer[i] << endl;
#endif // DEBUG

			}
		}

		//Load the images and process the textures for the object
		for (int i = 0; i < numTEXs; i++)
		{
			char tmp[MAX_PARSER_CHARS];
			char dir[MAX_PARSER_CHARS];
			char fname[MAX_PARSER_CHARS];
			sscanf(mesh->filename, "%[^/] %s", dir, fname);
			strcpy(tmp, dir);
			strcat(tmp, "/textures");
			strcat(tmp, fname);
			strcat(tmp, ".png"); ///Only loading DDS (?)
			textures[i] = createTexture2D(tmp);
#if DEBUG
			if (textures[i] == 0)
			{
				cout << "[Engine] ERROR: Failed to load texture! (maybe file doesn't exist under /textures directory or name doesn't match)" << endl;
			}
			bool flag = glIsTexture(textures[i]);
			if (!flag)
			{
				cout << "[Engine] ERROR: Texture " << textures[i] << " is invalid !" << endl;
			}
#endif // DEBUG

		}
		//Sorting texture vectors accordingly
		vector<vmath::vec2> uv = mesh->getUV(); //This is not a reference // is a copy
		vector<vmath::vec2> & refuv = mesh->getUV();
		vector<vmath::vec2> tmp(uv.size());
		for (unsigned int i = 0; i < mesh->getVertexCount(); i++)
		{
			tmp.at(i) = uv.at(mesh->getUVIndices().at(getArrayPos(mesh->getIndices(), i)));
		}

#if 0 ///Change this to log txt file
		std::cout << std::endl;
		std::cout << "UV non aligned coordinates:" << std::endl;
		for (unsigned int i = 0; i < refuv.size(); i++)
		{
			std::cout << refuv.at(i)[0] << " " << refuv.at(i)[1] << std::endl;
		}

		refuv.swap(tmp);
		tmp.clear();

		std::cout << "UV aligned coordinates:" << std::endl;
		for (unsigned int i = 0; i < refuv.size(); i++)
		{
			std::cout << mesh->getUV().at(i)[0] << " " << mesh->getUV().at(i)[1] << std::endl;
		}
#endif // 0


	}

	//Initialize data for Drawing Buffers
	glGenBuffers(numEBOs, EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[indices]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(unsigned int), &mesh->getIndices().front(), GL_STATIC_DRAW);

#if 0 ///Change this to log txt file
	for (unsigned int i = 0; i < mesh->getVertices().size(); i++)
		cout << mesh->getVertices().at(i)[0] << " " << mesh->getVertices().at(i)[1] << " " << mesh->getVertices().at(i)[2] << endl;

	for (unsigned int i = 0; i < mesh->getIndices().size(); i++)
		cout << "[" << mesh->getIndices().at(i) << "]" << endl;

	for (unsigned int i = 0; i < mesh->getUV().size(); i++)
		cout << mesh->getUV().at(i)[0] << " " << mesh->getUV().at(i)[1] << endl;
#endif // 0



	glCreateVertexArrays(numVAOs, VAO);
	glBindVertexArray(VAO[triangles]);

	glGenBuffers(numVBOs, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[vertices]);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(vmath::vec3), &mesh->getVertices().front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//Initializes modelMatrix to identity
	modelMatrix = vmath::mat4(vmath::vec4(1, 0, 0, 0), vmath::vec4(0, 1, 0, 0), vmath::vec4(0, 0, 1, 0), vmath::vec4(0, 0, 0, 1));

	//Initialization of texture
	bind(ENGINE_OBJ_PROGRAM_BIND);
	glBindTexture(GL_TEXTURE_2D, textures[tex0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[uvs]);
	glBufferData(GL_ARRAY_BUFFER, mesh->getUV().size() * sizeof(vmath::vec2), &mesh->getUV().front(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
}

void Object::render()
{
	GLfloat cColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, cColor);
	glBindVertexArray(VAO[triangles]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[indices]);
	glDrawElements(GL_TRIANGLES, (GLsizei)(mesh->getIndices().size()), GL_UNSIGNED_INT, NULL);
}

void Object::bind(GLenum flag)
{
	switch (flag)
	{
	case ENGINE_OBJ_PROGRAM_BIND:
		program->use();
		break;
	case ENGINE_OBJ_PROGRAM_UNBIND:
		program->use(0);
		break;
	}
}

GLuint & Object::getProgram()
{
	return program->getProgram();
}


Object::~Object()
{
	glDeleteBuffers(numEBOs, EBO);
	glDeleteBuffers(numVBOs, VBO);
	glDeleteVertexArrays(numVAOs, VAO);
	delete[] vertexShader;
	delete[] fragmentShader;
	delete[] mesh;
	delete[] program;

	for (int i = 0; i < numTEXs; i++)
	{
		if (glIsTexture(textures[i]))
		{
			glDeleteTextures(1, &textures[i]);
		}
	}
}

int Object::getArrayPos(std::vector<unsigned int> vector, unsigned int value)
{
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		if (vector.at(i) == value)
		{
			return i;
		}
	}
	return -1;
}

void Object::modelTransform(GLfloat scale, vmath::vec3 rotateDegrees, vmath::vec3 translate)
{
	modelMatrix = vmath::scale(scale) * vmath::rotate(vmath::radians(rotateDegrees[0]), vmath::radians(rotateDegrees[1]), vmath::radians(rotateDegrees[2])) * vmath::translate(translate);
}

void Object::update()
{
	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, modelMatrix);
}
