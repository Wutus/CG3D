#pragma once
#include "glwObject3D.h"

template<class Archive>
void serialize(Archive & archive, vec3 & vec, const unsigned int version)
{
	ar & vec.x & vec.y & vec.z;
}

template<class Archive>
void serialize(Archive & archive, mat4x4 & mat, const unsigned int version)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ar & mat[i][j];
		}
	}
}

class ObjectSerializer
{
public:
	ObjectSerializer();
	~ObjectSerializer();
};

