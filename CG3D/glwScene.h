#pragma once
#include "glwObject3D.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include "glwPointLight.h"
#include "glwCompoundObject3D.h"
#include "glwCamera.h"
#include "glwAdvancedShader.h"
#include "glwProjection.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>
#include <string>
#include <memory>

class glwScene
{
public:
	glwScene(const std::string & name);
	~glwScene();
	static std::unique_ptr<glwScene> LoadFromFile(const std::string & fileName);
	static std::unique_ptr<glwScene> LoadFromBytes(const std::vector<char> & bytes);
	static std::unique_ptr<glwScene> LoadFromStream(std::istream & stream);
	glwCompoundObject3D Objects;
	std::vector<std::shared_ptr<glwDirectionalLight>> dirLights;
	std::vector<std::shared_ptr<glwSpotLight>> spotLights;
	std::vector<std::shared_ptr<glwPointLight>> pointLights;
	void SetCamera(std::shared_ptr<glwCamera> camera);
	void SetShader(std::shared_ptr<glwAdvancedShader> shader);
	void SetProjection(std::shared_ptr<glwProjection> projection);
	void Draw();
	void SaveToFile(const std::string & fileName) const;
	std::vector<char> SaveToBytes() const;
	void SaveToStream(std::ostream & fileName) const;
	std::string name;
private:
	glwScene();

	std::shared_ptr<glwCamera> camera;
	std::shared_ptr<glwAdvancedShader> shader;
	std::shared_ptr<glwProjection> projection;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & name;
		ar & Objects;
		ar & dirLights;
		ar & spotLights;
		ar & pointLights;
		ar & camera;
		ar & shader;
		ar & projection;
	}
};

