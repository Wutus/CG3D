#pragma once
#include "glm/gtc/type_ptr.hpp"
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

using namespace glm;

class glwAdvancedShader;

class glwPreDrawable
{
public:
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) = 0;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	};
};

