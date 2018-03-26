#include "Bitmap.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Utils/stb_image.h"
#include "Utils/stb_image_write.h"

Bitmap::Bitmap(std::string path)
{
	data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
}

Bitmap::~Bitmap()
{
	if(data != NULL) free(data);
}

void Bitmap::writeBMP(const char * filepath, unsigned int bufferSize, void * pixels)
{
	stbi_write_bmp(filepath, 1024, 1024, 4, pixels);
}
