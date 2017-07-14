#include "model.h"
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;



Model::Model(const char * filename)
{
	char tmp[MAX_PARSER_CHARS];
	strcpy(tmp, filename);
	strcat(tmp, ".obj");
	loadObj(tmp);
	strcpy(this->filename, filename);
}

void Model::loadObj(const char * filename)
{
	FILE* file;
	char lineBuff[MAX_PARSER_CHARS];
	this->vertexCount = 0;
	this->normalCount = 0;
	this->trianglesCount = 0;
	this->textureCount = 0;
	unsigned int cnt = 0;

	clock_t start = clock();

	file = fopen(filename, "r");
	if (file != NULL)
	{
		while (fgets(lineBuff, MAX_PARSER_CHARS, file) != NULL)
		{
			if (lineBuff[0] == '#' || lineBuff[0] == 'm' || lineBuff[0] == 'o' || lineBuff[0] == 's' || lineBuff[0] == 'u')
			{
				cnt++;
				continue;
			}
			else if (lineBuff[0] == 'v' && lineBuff[1] == ' ')
			{
				vmath::vec3 vertexArr;
				sscanf(&lineBuff[2], "%f %f %f", &(vertexArr[0]), &(vertexArr[1]), &(vertexArr[2]));

				//FILLING VECTORS WITH DATA
				this->vertices.push_back(vertexArr);
				this->vertexCount++;
			}
			else if (lineBuff[0] == 'v' && lineBuff[1] == 't')
			{
				vmath::vec2 textureArr;
				sscanf(&lineBuff[3], "%f %f", &(textureArr[0]), &(textureArr[1]));

				//FILLING VECTORS WITH DATA
				this->textures.push_back(textureArr);
				this->textureCount++;
			}
			else if (lineBuff[0] == 'v' && lineBuff[1] == 'n')
			{
				vmath::vec3 normalArr;
				sscanf(&lineBuff[3], "%f %f %f", &(normalArr[0]), &(normalArr[1]), &(normalArr[2]));

				//FILLING VECTORS WITH DATA
				this->normals.push_back(normalArr);
				this->normalCount++;
			}
			else if (lineBuff[0] == 'f')
			{
				unsigned int indices[3], normals[3], textureIndex[3]; //Discarding normals for now
				sscanf(&lineBuff[2], "%u/%u/%u %u/%u/%u %u/%u/%u", &(indices[0]), &(textureIndex[0]), &(normals[0]), &(indices[1]), &(textureIndex[1]),
					&(normals[1]), &(indices[2]), &(textureIndex[2]), &(normals[2]));

				//FILLING VECTORS WITH DATA
				this->texturesIndex.push_back(textureIndex[0] - 1);
				this->texturesIndex.push_back(textureIndex[1] - 1);
				this->texturesIndex.push_back(textureIndex[2] - 1);

				this->indices.push_back(indices[0] - 1);
				this->indices.push_back(indices[1] - 1);
				this->indices.push_back(indices[2] - 1);
				this->trianglesCount++;
			}
			else
			{
				//This should not happen... Just to make sure...
				cout << "One line was wrongly(?) skipped" << endl;
				cnt++;
				continue;
			}
			cnt++;
		}
		fclose(file);

		clock_t end = clock();
		cout << "File read took " << float(end - start) / CLOCKS_PER_SEC << " seconds." << endl;

		//Rearange the vertices and normals
		//Print out results test
#if DEBUG
		cout << "Vertex Count: " << vertexCount << endl;
		cout << "Normal Count: " << normalCount << endl;
		cout << "Triang Count: " << trianglesCount << endl;
		cout << "UVs    Count: " << textureCount << endl;
#endif // DEBUG


	}
}

vector<vmath::vec3> & Model::getVertices()
{
	return vertices;
}

vector<vmath::vec2> & Model::getUV()
{
	return textures;
}

vector<unsigned int> & Model::getIndices()
{
	return indices;
}

vector<unsigned int> & Model::getUVIndices()
{
	return texturesIndex;
}

unsigned int & Model::getVertexCount()
{
	return vertexCount;
}


Model::~Model()
{
}
