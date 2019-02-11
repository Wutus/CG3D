#pragma once
#include <string>

class glwTexture2D
{
public:
	glwTexture2D(std::string filename, std::string type, bool flip = false);
	glwTexture2D(const glwTexture2D &) = delete;
	~glwTexture2D();
	int GetWidth() const;
	int GetHeight() const;
	int GetNrChannels() const;
	unsigned int GetID() const;
	std::string GetFileName() const;
	std::string GetType() const;
private:
	unsigned int Id;
	int width, height, nrChannels;
	std::string fileName;
	std::string type;
};

