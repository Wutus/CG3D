#pragma once
#include <string>

class Texture2D
{
public:
	unsigned int Id;
	Texture2D(std::string filename);
	~Texture2D();
	int GetWidth();
	int GetHeight();
private:
	int width, height, nrChannels;
};

