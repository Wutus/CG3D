#include "glwScene.h"
#include <ios>
#include <fstream>

glwScene::glwScene(const std::string & name) : Objects(std::shared_ptr<glwObject3D>(new glwObject3D(vec3(0,0,0), name + "_base")), name + "_objects"), name(name)
{
}


glwScene::~glwScene()
{
}

std::shared_ptr<glwScene> glwScene::LoadFromStream(std::istream & stream)
{
	return std::shared_ptr<glwScene>();
}

std::shared_ptr<glwScene> glwScene::LoadFromBytes(const std::vector<char> & bytes)
{
	return std::shared_ptr<glwScene>();
}

std::shared_ptr<glwScene> glwScene::LoadFromFile(const std::string & fileName)
{
	return std::shared_ptr<glwScene>();
}

void glwScene::SetCamera(std::shared_ptr<glwCamera> camera)
{
	this->camera = camera;
}

void glwScene::SetShader(std::shared_ptr<glwAdvancedShader> shader)
{
	this->shader = shader;
}

void glwScene::SetProjection(std::shared_ptr<glwProjection> projection)
{
	this->projection = projection;
}

void glwScene::Draw()
{
	Objects.PreDraw(*shader, mat4x4(1.0f));
	Objects.Draw(*shader, mat4x4(1.0f));
}

void glwScene::SaveToFile(const std::string & fileName)
{
	std::ifstream file(fileName, "wb");
}

std::vector<char> glwScene::SaveToBytes()
{
	return std::vector<char>();
}

void glwScene::SaveToStream(std::ostream & stream)
{

}
