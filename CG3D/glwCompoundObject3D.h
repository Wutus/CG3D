#pragma once
#include "glwObject3D.h"
#include "glwPointLight.h"
#include "glwSpotLight.h"
#include "glwDrawable.h"
#include "glwPreDrawable.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <memory>
#include <vector>

class glwCompoundObject3D : public glwObject3D, public glwDrawable, public glwPreDrawable
{
public:
	glwCompoundObject3D(std::shared_ptr<glwObject3D> base, const std::string & name = "");
	~glwCompoundObject3D();
	
	void AddObject(std::shared_ptr<glwObject3D> object);
	void RemoveObject(std::shared_ptr<glwObject3D> object);
	std::shared_ptr<glwObject3D> Find(const std::string & name);
	virtual void Draw(glwShader & shader, mat4x4 model = mat4x4(1.0f)) override;
	virtual glwCompoundObject3D *Clone(const std::string & name = "") override;
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
	
private:
	glwCompoundObject3D(vec3 pos, const std::string & name = "");
	std::vector<std::shared_ptr<glwObject3D>> objects;

	//serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & objects;
	};
};