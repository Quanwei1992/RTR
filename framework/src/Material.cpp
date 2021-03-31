#include "framework/Material.h"
#include "framework/Shader.h"
#include "framework/Texture2D.h"
#include "json.hpp"

using json = nlohmann::json;

void Material::setBool(const std::string& name, bool value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::BOOL;
	pv.b = value;
	_properties[name] = pv;
}

void Material::setInt(const std::string& name, int value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::INT;
	pv.i = value;
	_properties[name] = pv;
}

void Material::setFloat(const std::string& name, float value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::FLOAT;
	pv.f = value;
	_properties[name] = pv;
}

void Material::setVec2(const std::string& name, const glm::vec2& value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC2;
	pv.v2 = value;
	_properties[name] = pv;
}

void Material::setVec2(const std::string& name, float x, float y) 
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC2;
	pv.v2 = glm::vec2(x,y);
	_properties[name] = pv;
}

void Material::setVec3(const std::string& name, const glm::vec3& value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC3;
	pv.v3 = value;
	_properties[name] = pv;
}

void Material::setVec3(const std::string& name, float x, float y, float z) 
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC3;
	pv.v3 = glm::vec3(x, y,z);
	_properties[name] = pv;
}

void Material::setVec4(const std::string& name, const glm::vec4& value) 
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC4;
	pv.v4 = value;
	_properties[name] = pv;
}

void Material::setVec4(const std::string& name, float x, float y, float z, float w)
{
	PropertyValue pv;
	pv.Type = PropertyType::VEC4;
	pv.v4 = glm::vec4(x, y, z,w);
	_properties[name] = pv;
}

void Material::setMat2(const std::string& name, const glm::mat2& mat) 
{
	PropertyValue pv;
	pv.Type = PropertyType::MAT2;
	pv.m2 = mat;
	_properties[name] = pv;
}

void Material::setMat3(const std::string& name, const glm::mat3& mat) 
{
	PropertyValue pv;
	pv.Type = PropertyType::MAT3;
	pv.m3 = mat;
	_properties[name] = pv;
}

void Material::setMat4(const std::string& name, const glm::mat4& mat) 
{
	PropertyValue pv;
	pv.Type = PropertyType::MAT4;
	pv.m4= mat;
	_properties[name] = pv;
}

void Material::setTexture2D(const std::string& name, const Texture2D* texture) 
{
	PropertyValue pv;
	pv.Type = PropertyType::TEX2D;
	pv.p = (void*)texture;
	_properties[name] = pv;
}

Material* Material::Load(const std::string& filename)
{
	std::ifstream i(filename);
	json j;
	i >> j;

	Material* mtl = nullptr;
	std::ifstream materialFile;
	// ensure ifstream objects can throw exceptions:
	materialFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		materialFile.open(filename);
		json j;
		materialFile >> j;
		materialFile.close();

		std::string vertexShaderFileName = j["VertexShader"].get<std::string>();
		std::string fragmentShaderFileName = j["FragmentShader"].get<std::string>();
		Shader* shader = Shader::LoadShader(vertexShaderFileName.c_str(), fragmentShaderFileName.c_str());
		if (shader == nullptr)
		{
			std::cout << "ERROR::MATERIAL::LOAD_SHADER_FAILED" << std::endl;
			return nullptr;
		}

		mtl = new Material();
		mtl->_shader = shader;
		auto& properties = j["Properties"];
		for (auto& property : properties)
		{
			auto name = property["name"].get<std::string>();
			auto type = property["type"].get<std::string>();
			if (type == "Texture2D")
			{
				auto value = property["value"].get<std::string>();
				auto texture = Texture2D::Load(value.c_str());
				if (texture != nullptr)
				{
					mtl->_textures.push_back(texture);
					mtl->setTexture2D(name, texture);
				}
				else {
					std::cout << "ERROR::MATERIAL::LOAD TEXTURE FAILED " << value << std::endl;
				}
			}
		}
	}
	catch (std::ifstream::failure)
	{
		std::cout << "ERROR::MATERIAL::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}
	return mtl;
}

Material::~Material()
{
	if (_shader) {
		delete _shader;
		_shader = nullptr;
	}
	for (auto tex : _textures)
	{
		delete tex;
	}
	_textures.clear();
}

