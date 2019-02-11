#pragma once

#include "glm/gtc/type_ptr.hpp"
#include "glwTexture2D.h"
#include <memory>

using namespace glm;

class Material
{
public:
	Material(std::shared_ptr<glwTexture2D> diffuseTexture, std::shared_ptr<glwTexture2D> specularTexture = nullptr);
	~Material();
	std::shared_ptr<glwTexture2D> getDiffuseTexture();
	std::shared_ptr<glwTexture2D> getSpecularTexture();
	void setDiffuseTexture(std::shared_ptr<glwTexture2D> diffuseTexture);
	void setSpecularTexture(std::shared_ptr<glwTexture2D> specularTexture);
private:
	std::shared_ptr<glwTexture2D> diffuseTexture;
	std::shared_ptr<glwTexture2D> specularTexture;
};

