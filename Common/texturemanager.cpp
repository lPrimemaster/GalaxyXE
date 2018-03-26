#include "texturemanager.h"
#include "../Textures/texture.h"

TextureManager::~TextureManager()
{
	buffer.clear();
}

void TextureManager::createTextureType(const std::string& identifier)
{
	if (loc.empty() || !loc.count(identifier))
	{
		auto emplaced = loc.emplace(identifier, std::vector<std::string>());
		std::cout << "[TextureManager] Initializing TextureType -> " << identifier << std::endl;
	}
	else
		std::cout << "[TextureManager] Duplicate name initializing. Ignoring..." << std::endl;
}

void TextureManager::deleteTextureType(const std::string & identifier)
{
	if (loc.count(identifier))
	{
		loc.erase(identifier);
		std::cout << "[TextureManager] Deleted TextureType -> " << identifier << std::endl;
	}
	else
		std::cout << "[TextureManager] Could not find TextureType -> " << identifier << std::endl;
}

void TextureManager::loadTextures()
{
	for (const auto& data : loc)
	{
		buffer.emplace(data.first, std::map<std::string, Texture*>());
		for (const auto& path : data.second)
		{
			Texture* newtexture = new Texture();
			loader.loadTexture(*newtexture, path);
			buffer[data.first].emplace(path, newtexture);
		}
	}
}
