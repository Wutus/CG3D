#include "Material.h"
#include <stdexcept>

Material::Material(std::shared_ptr<glwTexture2D> diffuseTexture, std::shared_ptr<glwTexture2D> specularTexture)
{
	if (diffuseTexture == nullptr)
	{
		throw std::invalid_argument("diffuseTexture cannot be null");
	}
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
}

Material::~Material()
{
}

std::shared_ptr<glwTexture2D> Material::getDiffuseTexture()
{
	return diffuseTexture;
}

std::shared_ptr<glwTexture2D> Material::getSpecularTexture()
{
	return specularTexture != nullptr ? specularTexture : diffuseTexture;
}

void Material::setDiffuseTexture(std::shared_ptr<glwTexture2D> diffuseTexture)
{
	if (diffuseTexture == nullptr)
	{
		throw std::invalid_argument("diffuseTexture cannot be null");
	}
	this->diffuseTexture = diffuseTexture;
}

void Material::setSpecularTexture(std::shared_ptr<glwTexture2D> specularTexture)
{
	this->specularTexture = specularTexture;
}
