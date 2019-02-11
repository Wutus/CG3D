#include "glwCompoundObject3D.h"
#include <algorithm>


glwCompoundObject3D::glwCompoundObject3D(std::shared_ptr<glwObject3D> base) : glwDrawableObject3D(base->position())
{
	this->base = base;
	this->drawable_base = nullptr;
}

glwCompoundObject3D::glwCompoundObject3D(std::shared_ptr<glwDrawableObject3D> base) : glwDrawableObject3D(base->position())
{
	this->base = base;
	this->drawable_base = base;
}

glwCompoundObject3D::~glwCompoundObject3D()
{
}

void glwCompoundObject3D::AddDrawable(std::shared_ptr<glwDrawableObject3D> drawable)
{
	drawables.push_back(drawable);
}

void glwCompoundObject3D::AddUndrawable(std::shared_ptr<glwObject3D> undrawable)
{
	undrawables.push_back(undrawable);
}

void glwCompoundObject3D::RemoveObject(std::shared_ptr<glwObject3D> object)
{
	drawables.erase(std::remove(drawables.begin(), drawables.end(), object), drawables.end());
	undrawables.erase(std::remove(undrawables.begin(), undrawables.end(), object), undrawables.end());
}

void glwCompoundObject3D::Draw(glwShader & shader, mat4x4 model)
{
	model = model*this->model();
	if (drawable_base != nullptr)
	{
		drawable_base->Draw(shader, model);
	}

	for (auto drawable : drawables)
	{
		drawable->Draw(shader, model*drawable->model());
	}
}
