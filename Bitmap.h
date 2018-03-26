#pragma once
#include <iostream>

class Bitmap
{
public:
	Bitmap(std::string path);
	~Bitmap();

	const unsigned char* operator()()
	{
		return data;
	}

	const int getChannels() const
	{
		return channels;
	}

	const int getHeight() const
	{
		return height;
	}

	const int getWidth() const
	{
		return width;
	}

	static void writeBMP(const char* filepath, unsigned int bufferSize, void* pixels);

private:
	unsigned char* data;
	int width, height;
	int channels;
};

