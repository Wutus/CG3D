#include "glwAdvancedShader.h"

#include "glwDefines.h"
#include <string>

using namespace std;

glwAdvancedShader::glwAdvancedShader(std::string vertexPath, std::string fragmentPath) : glwShader(vertexPath, fragmentPath)
{
	resetLights();
}


glwAdvancedShader::~glwAdvancedShader()
{
}

void glwAdvancedShader::addPointLight(const glwPointLight & pointLight, mat4x4 system)
{
	string path = getLightPath(POINTLIGHT);
	addLightSource(path, pointLight);

	setVec3(path + ".position", vec3(system*vec4(pointLight.position(), 1.0f)));
	setVec3(path + ".distanceFactor", pointLight.distanceFactor);

	++pointlights;
	setInt(POINTLIGHTSIZE, pointlights);
}

void glwAdvancedShader::addSpotLight(const glwSpotLight & spotLight, mat4x4 system)
{
	string path = getLightPath(SPOTLIGHT);
	addLightSource(path, spotLight);

	setVec3(path + ".position", vec3(system*vec4(spotLight.position(),1.0f)));
	setVec3(path + ".distanceFactor", spotLight.distanceFactor);
	setVec3(path + ".direction", vec3(system*vec4(spotLight.direction, 1.0f)));
	setFloat(path + ".cutOff", cos(radians(spotLight.cutOff)));
	setFloat(path + ".outerCutOff", cos(radians(spotLight.outerCutOff)));

	++spotlights;
	setInt(SPOTLIGHTSIZE, spotlights);
}

void glwAdvancedShader::addDirectionalLight(const glwDirectionalLight & dirLight)
{
	string path = getLightPath(DIRLIGHT);
	addLightSource(path, dirLight);

	setVec3(path + ".direction", dirLight.direction);

	++dirlights;
	setInt(DIRLIGHTSIZE, dirlights);
}

void glwAdvancedShader::setProjection(const glwProjection & projection)
{
	setMat4(PROJECTION, projection.projection());
}

void glwAdvancedShader::setModelMatrix(const mat4x4 & model)
{
	setMat4(MODEL, model);
}

void glwAdvancedShader::setMaterial(const glwMaterial & material)
{
	setFloat(MATERIAL + ".shininess", material.shiness);
	setInt(MATERIAL + ".diffuse", material.getDiffuseTexture()->GetID());
	setInt(MATERIAL + ".specular", material.getSpecularTexture()->GetID());
}

void glwAdvancedShader::resetLights()
{
	pointlights = spotlights = dirlights = 0;
	setInt(POINTLIGHTSIZE, pointlights);
	setInt(SPOTLIGHTSIZE, spotlights);
	setInt(DIRLIGHTSIZE, dirlights);
}

void glwAdvancedShader::addLightSource(string lightPath, const glwLightSource & lightSource)
{
	setVec3(lightPath + ".ambient", lightSource.ambient);
	setVec3(lightPath + ".diffuse", lightSource.diffuse);
	setVec3(lightPath + ".specular", lightSource.specular);
}

string glwAdvancedShader::getLightPath(LIGHTTYPE type)
{
	switch (type) {
	case POINTLIGHT:
		return POINTLIGHTS + "[" + to_string(pointlights) + "]";
	case SPOTLIGHT:
		return SPOTLIGHTS + "[" + to_string(spotlights) + "]";
	case DIRLIGHT:
		return DIRLIGHTS + "[" + to_string(dirlights) + "]";
	default:
		return "";
	}
}
