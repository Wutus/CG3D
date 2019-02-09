#pragma once
#include <string>

class glwTexture2D
{
public:
	unsigned int Id;
	glwTexture2D(std::string filename);
	~glwTexture2D();
	int GetWidth();
	int GetHeight();
private:
	int width, height, nrChannels;
};

