#pragma once
#include <string>

class glwTexture2D
{
public:
	glwTexture2D(std::string filename, std::string type, bool flip = false);
	glwTexture2D(const glwTexture2D &) = delete;
	~glwTexture2D();
	int GetWidth();
	int GetHeight();
	int GetNrChannels();
	unsigned int GetID();
	std::string GetFileName();
	std::string GetType();
private:
	unsigned int Id;
	int width, height, nrChannels;
	std::string fileName;
	std::string type;
};

