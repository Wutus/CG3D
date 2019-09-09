#include "glwScene.h"
#include <ios>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

glwScene::glwScene() : Objects(std::shared_ptr<glwObject3D>(new glwObject3D(vec3(0, 0, 0),  + "_base")), + "_objects"), name("")
{

}

glwScene::glwScene(const std::string & name) : Objects(std::shared_ptr<glwObject3D>(new glwObject3D(vec3(0,0,0), name + "_base")), name + "_objects"), name(name)
{
}


glwScene::~glwScene()
{
}

std::unique_ptr<glwScene> glwScene::LoadFromStream(std::istream & stream)
{
	boost::archive::text_iarchive ia(stream);
	std::unique_ptr<glwScene> scene(new glwScene());
	ia >> *scene;
	return scene;
}

std::unique_ptr<glwScene> glwScene::LoadFromBytes(const std::vector<char> & bytes)
{
	boost::iostreams::stream<boost::iostreams::array_source> boost_stream(bytes.data(), bytes.size());
	std::istream & stream = boost_stream;
	boost::archive::text_iarchive ia(stream);
	std::unique_ptr<glwScene> scene(new glwScene());
	ia >> *scene;
	return scene;
}

std::unique_ptr<glwScene> glwScene::LoadFromFile(const std::string & fileName)
{
	std::ifstream stream(fileName);
	boost::archive::text_iarchive ia(stream);
	std::unique_ptr<glwScene> scene(new glwScene());
	ia >> *scene;
	return scene;
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

void glwScene::SaveToFile(const std::string & fileName) const
{
	std::ofstream stream(fileName);
	boost::archive::text_oarchive oa(stream);
	oa << *this;
}

std::vector<char> glwScene::SaveToBytes() const
{
	std::vector<char> vector;
	boost::iostreams::back_insert_device<std::vector<char>> sink{vector};
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::vector<char>>> boost_stream(sink);
	std::ostream & stream = boost_stream;
	boost::archive::text_oarchive oa(static_cast<std::ostream &>(stream));
	oa << *this;
	return vector;
}

void glwScene::SaveToStream(std::ostream & stream) const
{
	boost::archive::text_oarchive oa(stream);
	oa << *this;
}
