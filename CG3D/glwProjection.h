#pragma once
#include "glm/gtc/type_ptr.hpp"
#include "glwPreDrawable.h"
#include "glwBaseSerialization.hpp"
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

using namespace glm;

class glwProjection : glwPreDrawable
{
public:
	glwProjection(int screenWidth, int screenHeight, float FOV = 45, float nearDist = 0.1f, float farDist = 100.0f);
	~glwProjection();
	const mat4x4 & projection() const;
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
private:
	glwProjection() = default;
	mat4x4 _projection;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _projection;
	};
};

