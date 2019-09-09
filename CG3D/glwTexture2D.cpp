#include "glwTexture2D.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <fstream>
#include <iostream>

glwTexture2D::glwTexture2D(std::string filename, std::string type, bool flip)
{
	loadTexture(filename, type, flip);
}

glwTexture2D::~glwTexture2D()
{
}

void glwTexture2D::loadTexture()
{
	loadTexture(filename, type, flipped);
}

void glwTexture2D::loadTexture(std::string filename, std::string type, bool flip)
{
	this->filename = filename;
	this->type = type;
	this->flipped = flip;
	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);

	stbi_set_flip_vertically_on_load(flip);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	this->type = type;
}

int glwTexture2D::GetWidth() const
{
	return width;
}

int glwTexture2D::GetHeight() const
{
	return height;
}

int glwTexture2D::GetNrChannels() const
{
	return nrChannels;
}

unsigned int glwTexture2D::GetID() const
{
	return Id;
}

std::string glwTexture2D::GetFileName() const
{
	return filename;
}

std::string glwTexture2D::GetType() const
{
	return type;
}
