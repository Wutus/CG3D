#pragma once
#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>

class glwTexture2D
{
public:
	glwTexture2D(std::string filename, std::string type, bool flip = false);
	glwTexture2D(const glwTexture2D &) = delete;
	~glwTexture2D();
	int GetWidth() const;
	int GetHeight() const;
	int GetNrChannels() const;
	unsigned int GetID() const;
	std::string GetFileName() const;
	std::string GetType() const;
private:
	bool flipped;
	unsigned int Id;
	int width, height, nrChannels;
	std::string filename;
	std::string type;

	void loadTexture();
	void loadTexture(std::string filename, std::string type, bool flip);

	friend class boost::serialization::access;
	template<class Archive>
	void save(Archive & ar, const unsigned int version)
	{
		ar & filename;
		ar & type;
		ar & flipped;
	};

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & filename;
		ar & type;
		ar & flipped;
		loadTexture();
	};

	BOOST_SERIALIZATION_SPLIT_MEMBER();
};

