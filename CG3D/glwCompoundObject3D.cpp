#include "glwCompoundObject3D.h"
#include <algorithm>

using namespace std;

glwCompoundObject3D::glwCompoundObject3D(std::shared_ptr<glwObject3D> base, const std::string & name) : glwObject3D(base->position(), name)
{
	this->_model = base->model();
	this->_pos = base->position();
	base->Reset();
	objects.push_back(base);
}

glwCompoundObject3D::~glwCompoundObject3D()
{
}

void glwCompoundObject3D::AddObject(std::shared_ptr<glwObject3D> object)
{
	if(std::find(objects.begin(), objects.end(), object) == objects.end())
		objects.push_back(object);
}

void glwCompoundObject3D::RemoveObject(std::shared_ptr<glwObject3D> object)
{
	objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

std::shared_ptr<glwObject3D> glwCompoundObject3D::Find(const std::string & name)
{
	auto res = find_if(objects.begin(), objects.end(), [&name](auto &it) {return it->name == name; });
	if (res != objects.end())
	{
		return *res;
	}
	else
	{
		return nullptr;
	}
}

void glwCompoundObject3D::Draw(glwShader & shader, mat4x4 model)
{
	model = model*this->model();
	for (shared_ptr<glwObject3D> ptr : objects)
	{
		shared_ptr<glwDrawable> drawable = dynamic_pointer_cast<glwDrawable>(ptr);
		if (drawable != nullptr)
		{
			drawable->Draw(shader, model);
		}
	}
}

glwCompoundObject3D *glwCompoundObject3D::Clone(const std::string & name)
{
	glwCompoundObject3D *res = new glwCompoundObject3D(position(),name);
	res->_model = _model;
	res->_pos = _pos;
	shared_ptr<glwObject3D> s(res);
	for (shared_ptr<glwObject3D> ptr : objects)
	{
		res->AddObject(shared_ptr<glwObject3D>(ptr->Clone()));
	}
	return res;
}

void glwCompoundObject3D::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	model = model * this->model();
	for (shared_ptr<glwObject3D> ptr : objects)
	{
		shared_ptr<glwPreDrawable> predrawable = dynamic_pointer_cast<glwPreDrawable>(ptr);
		if (predrawable != nullptr)
		{
			predrawable->PreDraw(shader, model);
		}
	}
}

glwCompoundObject3D::glwCompoundObject3D(vec3 pos, const std::string & name) : glwObject3D(pos, name)
{
	
}