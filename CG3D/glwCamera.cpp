#include "glwCamera.h"
#include "glwAdvancedShader.h"

#include "glwDefines.h"

const vec3 glwCamera::up = vec3(0.0f, 1.0f, 0.0f);

glwCamera::glwCamera(vec3 pos, const std::string & name) : glwObject3D(pos, name)
{
	target = vec3(1.0f, 0.0f, 0.0f);
}

glwCamera::glwCamera(vec3 pos, vec3 target, const std::string & name) : glwObject3D(pos, name)
{
	this->target = target;
}

glwCamera::glwCamera(vec3 pos, std::shared_ptr<glwObject3D> target, const std::string & name) : glwObject3D(pos, name)
{
	this->target = target->position();
}

glwCamera::~glwCamera()
{
}

void glwCamera::LookAt(std::shared_ptr<glwObject3D> target)
{
	this->target = target->position();
}

void glwCamera::LookAt(vec3 target)
{
	this->target = target;
}

void glwCamera::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	vec3 t_target = vec3(model*vec4(target, 1.0f));
	vec3 t_pos = vec3(model*vec4(_pos, 1.0f));
	mat4x4 view_matrix = lookAt(t_pos, t_target, up);
	
	shader.setMat4(VIEW, view_matrix);
	shader.setVec3(VIEWPOS, t_pos);
}
