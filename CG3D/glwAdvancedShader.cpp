#include "glwAdvancedShader.h"
#include <string>

using namespace std;
const string MODEL = "model";
const string VIEW = "view";
const string PROJECTION = "projection";
const string VIEWPOS = "viewPos";
const string DIRLIGHTS = "dirLights";
const string POINTLIGHTS = "pointLights";
const string SPOTLIGHTS = "spotLights";
const string DIRLIGHTSIZE = "dirLightSize";
const string POINTLIGHTSIZE = "pointLightSize";
const string SPOTLIGHTSIZE = "spotLightSize";

glwAdvancedShader::glwAdvancedShader(std::string vertexPath, std::string fragmentPath) : glwShader(vertexPath, fragmentPath)
{
	resetLights();
}


glwAdvancedShader::~glwAdvancedShader()
{
}

void glwAdvancedShader::setCamera(const glwCamera & camera)
{
	setMat4(VIEW, camera.model());
	setVec3(VIEWPOS, camera.position());
}

void glwAdvancedShader::addPointLight(const glwPointLight & pointLight)
{
	string path = getLightPath(POINTLIGHT);
	addLightSource(path, pointLight);

	setVec3(path + ".position", pointLight.position());
	setVec3(path + ".distanceFactor", pointLight.distanceFactor);

	++pointlights;
	setInt(POINTLIGHTSIZE, pointlights);
}

void glwAdvancedShader::addSpotLight(const glwSpotLight & spotLight)
{
	string path = getLightPath(SPOTLIGHT);
	addLightSource(path, spotLight);

	setVec3(path + ".position", spotLight.position());
	setVec3(path + ".distanceFactor", spotLight.distanceFactor);
	setVec3(path + ".direction", spotLight.direction);
	setFloat(path + ".cutOff", spotLight.cutOff);
	setFloat(path + ".outerCutOff", spotLight.outerCutOff);

	++spotlights;
	setInt(SPOTLIGHTSIZE, spotlights);
}

void glwAdvancedShader::addDirectionalLight(const glwDirectionalLight & dirLight)
{
	string path = getLightPath(SPOTLIGHT);
	addLightSource(path, dirLight);

	setVec3(path + ".direction", dirLight.direction);

	++dirlights;
	setInt(DIRLIGHTSIZE, dirlights);
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
	}
}
