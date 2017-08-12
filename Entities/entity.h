#pragma once
#include "../Models/model.h"
#include "../Models/loader.h"
#include <string>

class Entity
{
public:
	Entity(Loader& loader, std::string& modelPath);
	Entity(Model& model);
	~Entity();

	Model& getModel() const;

protected:
	Model* model;
};

