#include "Bitmap.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

Bitmap::Bitmap(std::string path)
{
	data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
}

Bitmap::~Bitmap()
{
	if(data != NULL) free(data);
}
