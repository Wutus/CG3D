#include "glwModelObject3D.h"

glwModelObject3D::glwModelObject3D(std::shared_ptr<glwModel> model3d, vec3 position, mat4x4 internal) : glwDrawableObject3D(position)
{
	_model3d = model3d;
	_internal = internal;
}

glwModelObject3D::~glwModelObject3D()
{
}

void glwModelObject3D::Draw(glwShader & shader, mat4x4 model)
{
	model = model * _internal;
	model = model * this->model();
	_model3d->Draw(shader, model);
}
