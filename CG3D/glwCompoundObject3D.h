#pragma once
#include "glwObject3D.h"
#include "glwDrawableObject3D.h"
#include <memory>
#include <vector>

class glwCompoundObject3D : public glwDrawableObject3D
{
public:
	glwCompoundObject3D(std::shared_ptr<glwObject3D> base);
	glwCompoundObject3D(std::shared_ptr<glwDrawableObject3D> base);
	~glwCompoundObject3D();
	
	void AddDrawable(std::shared_ptr<glwDrawableObject3D> drawable);
	void AddUndrawable(std::shared_ptr<glwObject3D> undrawable);
	void RemoveObject(std::shared_ptr<glwObject3D> object);

	// Inherited via glwObject3D
	virtual vec3 & position() override;
	virtual mat4x4 & model() override;

	// Inherited via glwDrawableObject3D
	virtual void Draw(glwShader & shader, mat4x4 model = mat4x4(1.0f)) override;
private:
	std::vector<std::shared_ptr<glwObject3D>> undrawables;
	std::vector<std::shared_ptr<glwDrawableObject3D>> drawables;
	std::shared_ptr<glwObject3D> base;
	std::shared_ptr<glwDrawableObject3D> drawable_base;
};
