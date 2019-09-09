#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

namespace boost {
namespace serialization {

template<class Archive, glm::length_t Size, class ValueType, glm::qualifier Qualifier>
inline void serialize(Archive & ar, glm::vec<Size, ValueType, Qualifier> & value, const unsigned int version)
{
	for (int i = 0; i < Size; ++i)
		ar & value[i];
}

template<class Archive, glm::length_t Size1, glm::length_t Size2, class ValueType, glm::qualifier Qualifier>
inline void serialize(Archive & ar, glm::mat<Size1, Size2, ValueType, Qualifier> & value, const unsigned int version)
{
	for (int i = 0; i < Size1; ++i)
		for (int j = 0; j < Size2; ++j)
			ar & value[i][j];
}

} // serialization
} // boost