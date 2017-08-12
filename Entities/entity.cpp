#include "entity.h"
#include <stdexcept>



Entity::Entity(Loader & loader, std::string & modelPath)
{
	//Exceptions are being handled in the Loader class
	loader.setInternalPath(modelPath);
	loader.loadFromObj(*model);
}

Entity::Entity(Model & model)
{
	this->model = new Model(model);
}

Entity::~Entity()
{
}

Model & Entity::getModel() const
{
	return *model;
}
