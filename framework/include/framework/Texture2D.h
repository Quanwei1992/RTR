#pragma once
#include <string>
class Texture2D
{


public:
	static Texture2D* Load(const std::string& filename);
private:
	Texture2D();
	unsigned int _textureID;
};