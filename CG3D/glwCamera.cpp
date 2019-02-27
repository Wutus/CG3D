#include "glwCamera.h"
#include "glwAdvancedShader.h"

const vec3 glwCamera::up = vec3(0.0f, 1.0f, 0.0f);

glwCamera::glwCamera(vec3 pos) : glwObject3D(pos)
{
}

glwCamera::glwCamera(vec3 pos, vec3 target) : glwObject3D(pos)
{
	_model = glm::lookAt(pos, target, up);
}

glwCamera::glwCamera(vec3 pos, std::shared_ptr<glwObject3D> target) : glwObject3D(pos)
{
	_model = glm::lookAt(pos, target->position(), up);
}

glwCamera::~glwCamera()
{
}

void glwCamera::LookAt(std::shared_ptr<glwObject3D> target)
{
	_model = glm::lookAt(_pos, target->position(), up);
}

void glwCamera::LookAt(vec3 target)
{
	_model = glm::lookAt(_pos, target, up);
}

void glwCamera::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	shader.setCamera(*this, model);
}
