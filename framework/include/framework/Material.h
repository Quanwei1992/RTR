#pragma once
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include <map>

class Shader;
class Texture2D;

enum class PropertyType
{
	BOOL,
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4,
	TEX2D
};

struct PropertyValue
{
	PropertyType Type;
	union
	{
		bool b;
		int i;
		float f;
		void* p;
		glm::vec2 v2;
		glm::vec3 v3;
		glm::vec4 v4;
		glm::mat2 m2;
		glm::mat3 m3;
		glm::mat4 m4;
	};
};

class Material
{
public:

	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) ;
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value);
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) ;
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) ;
	void setVec2(const std::string& name, float x, float y) ;
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) ;
	void setVec3(const std::string& name, float x, float y, float z) ;
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) ;
	void setVec4(const std::string& name, float x, float y, float z, float w);
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) ;
	// 
	void setMat3(const std::string& name, const glm::mat3& mat) ;
	// 
	void setMat4(const std::string& name, const glm::mat4& mat) ;

	void setTexture2D(const std::string& name, const Texture2D* texture) ;

public:
	static Material* Load(const std::string& filename);
	~Material();

private:
	Shader* _shader;
	std::vector<Texture2D*> _textures;
	std::map<std::string, int> fuck;
	std::map<std::string, PropertyValue> _properties;
};