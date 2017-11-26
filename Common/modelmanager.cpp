#include "modelmanager.h"

void ModelManager::createModelType(const std::string& identifier)
{
	if (loc.empty() || !loc.count(identifier))
	{
		auto emplaced = loc.emplace(identifier, std::vector<std::string>());
		std::cout << "[ModelManager] Initializing ModelType -> " << identifier << std::endl;
	}
	else
		std::cout << "[ModelManager] Duplicate name initializing. Ignoring..." << std::endl;
}

void ModelManager::deleteModelType(const std::string & identifier)
{
	if (loc.count(identifier))
	{
		loc.erase(identifier);
		std::cout << "[ModelManager] Deleted ModelType -> " << identifier << std::endl;
	}
	else
		std::cout << "[ModelManager] Could not find ModelType -> " << identifier << std::endl;
}

void ModelManager::deleteAllData()
{
	buffer.clear();
	std::cout << "[ModelManager] Successfully cleared all ModelTypes from buffer." << std::endl;
}

void ModelManager::loadModels()
{
	for (const auto& data : loc)
	{
		buffer.emplace(data.first, std::vector<Model>());
		for (const auto& path : data.second)
		{
			Model newmodel;
			loader.loadModel(newmodel, path);
			buffer[data.first].push_back(newmodel);
		}
	}
}
