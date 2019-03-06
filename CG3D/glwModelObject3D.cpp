#include "glwModelObject3D.h"

glwModelObject3D::glwModelObject3D(std::shared_ptr<glwModel> model3d, vec3 position, const std::string & name, mat4x4 internal) : glwObject3D(position, name)
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

glwModelObject3D *glwModelObject3D::Clone(const std::string & name)
{
	glwModelObject3D *res = new glwModelObject3D(_model3d, _pos, name, _internal);
	res->_model = _model;
	return res;
}
