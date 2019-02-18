#pragma once
#include "glwShader.h"
#include "glwObject3D.h"
#include "glwDrawable.h"

class glwDrawableObject3D : public glwObject3D, public glwDrawable
{
public:
	glwDrawableObject3D(vec3 pos, const string & name = "");
	virtual ~glwDrawableObject3D();
};

