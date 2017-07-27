#pragma once
#include "../types.h"
#include "tLoader.h"
#define MAX_PARSER_CHARS 128

class Model
{
public:
	Model(const char * filename);
	void loadObj(const char * filename);
	vector<vmath::vec3> & getVertices();
	vector<vmath::vec2> & getUV();
	vector<unsigned int> & getIndices();
	vector<unsigned int> & getUVIndices();
	unsigned int & getVertexCount();
	unsigned int & getTextureCount();
	~Model();

	char filename[MAX_PARSER_CHARS];

private:
	vector<vmath::vec3> vertices;
	vector<unsigned int> indices;
	vector<vmath::vec3> normals;
	vector<unsigned int> normalsIndex;
	vector<vmath::vec2> textures;
	vector<unsigned int> texturesIndex;

	unsigned int vertexCount;
	unsigned int normalCount;
	unsigned int textureCount;
	unsigned int trianglesCount;

};

