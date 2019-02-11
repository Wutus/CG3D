#include "glwMaterial.h"
#include <stdexcept>

std::shared_ptr<glwTexture2D> glwMaterial::defaultTexture = nullptr;

glwMaterial::glwMaterial(std::shared_ptr<glwTexture2D> ambientTexture, std::shared_ptr<glwTexture2D> diffuseTexture, std::shared_ptr<glwTexture2D> specularTexture, float shininess)
{
	this->ambientTexture = ambientTexture;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	this->shininess = shininess;
	if (checkNull())
	{
		throw std::invalid_argument("ambientTexture and diffuseTexture cannot be both null");
	}
}

glwMaterial::~glwMaterial()
{
}

const std::shared_ptr<glwTexture2D> glwMaterial::getAmbientTexture() const
{
	if (ambientTexture == nullptr)
	{
		return diffuseTexture;
	}
	else
	{
		return ambientTexture;
	}
}

const std::shared_ptr<glwTexture2D> glwMaterial::getDiffuseTexture() const
{
	if (diffuseTexture == nullptr)
	{
		return ambientTexture;
	}
	else
	{
		return diffuseTexture;
	}
}

const std::shared_ptr<glwTexture2D> glwMaterial::getSpecularTexture() const
{
	if (specularTexture == nullptr)
	{
		if (diffuseTexture == nullptr)
		{
			return ambientTexture;
		}
		else
		{
			return diffuseTexture;
		}
	}
	else
	{
		return specularTexture;
	}
}

void glwMaterial::setAmbientTexture(std::shared_ptr<glwTexture2D> ambientTexture)
{
	if (diffuseTexture == nullptr && ambientTexture == nullptr)
	{
		throw std::invalid_argument("ambientTexture and diffuseTexture cannot be both null");
	}
	this->ambientTexture = ambientTexture;
}

void glwMaterial::setDiffuseTexture(std::shared_ptr<glwTexture2D> diffuseTexture)
{
	if (ambientTexture == nullptr && diffuseTexture == nullptr)
	{
		throw std::invalid_argument("ambientTexture and diffuseTexture cannot be both null");
	}
	this->diffuseTexture = diffuseTexture;
}

void glwMaterial::setSpecularTexture(std::shared_ptr<glwTexture2D> specularTexture)
{
	this->specularTexture = specularTexture;
}

bool glwMaterial::checkNull()
{
	//return ambientTexture == nullptr && diffuseTexture == nullptr;
	if (defaultTexture == nullptr)
	{
		defaultTexture = std::shared_ptr<glwTexture2D>(new glwTexture2D("resources/black.jpg", "texture_ambient"));
	}
	ambientTexture = defaultTexture;
	return false;
}
