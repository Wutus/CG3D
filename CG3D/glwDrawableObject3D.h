#pragma once
#include "glwShader.h"
#include "glwObject3D.h"
#include "glwDrawable.h"

class glwDrawableObject3D : public glwObject3D, public glwDrawable
{
public:
	glwDrawableObject3D(vec3 pos, const std::string & name = "");
	virtual glwDrawableObject3D *Clone(const std::string & name = "") = 0;
	virtual ~glwDrawableObject3D();
};

