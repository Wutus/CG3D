#include "glwScene.h"

glwScene::glwScene(const std::string & name) : Objects(std::shared_ptr<glwObject3D>(new glwObject3D(vec3(0,0,0), name + "_base")), name + "_objects"), name(name)
{
}


glwScene::~glwScene()
{
}
