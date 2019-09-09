#pragma once

#include "glwDrawable.h"
#include "glwObject3D.h"
#include "glwModel.h"
#include "glwBaseSerialization.hpp"
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>
#include <memory>

class glwModelObject3D : public glwDrawable, public glwObject3D
{
public:
	glwModelObject3D(std::shared_ptr<glwModel> model3d, vec3 position, const std::string & name = "", mat4x4 internal = mat4x4(1.0f));
	~glwModelObject3D();

	// Inherited via glwDrawableObject3D
	virtual void Draw(glwShader & shader, mat4x4 model = mat4x4(1.0f)) override;
	virtual glwModelObject3D *Clone(const std::string & name = "") override;
private:
	std::shared_ptr<glwModel> _model3d;
	mat4x4 _internal;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<glwDrawable>(*this);
		ar & boost::serialization::base_object<glwObject3D>(*this);
		ar & _model3d;
		ar & _internal;
	};
};

