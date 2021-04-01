#include "framework/Material.h"
#include "framework/Shader.h"
#include "framework/Texture2D.h"
#include "json.hpp"
#include <cassert>

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
			else if (type == "VEC4")
			{
			 	const auto& value = property["value"];
				if (value.size() != 4)
				{
					std::cout << "ERROR::MATERIAL::PROPERTY VALUE WRONG FORMAT " << name << std::endl;
					delete mtl;
					return nullptr;
				}
				mtl->setVec4(name,value[0].get<float>(), value[1].get<float>(), value[2].get<float>(), value[3].get<float>());
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

void Material::setupShaderUniforms()
{
	unsigned int texureIndex = 0;
	_shader->use();
	for (auto kv : _properties)
	{
		auto name = kv.first;
		const auto& value = kv.second;
		switch (value.Type)
		{
		default:
			break;
		case PropertyType::BOOL:
			_shader->setBool(name, value.b);
			break;
		case PropertyType::INT:
			_shader->setInt(name, value.i);
			break;
		case PropertyType::FLOAT:
			_shader->setFloat(name, value.f);
			break;
		case PropertyType::VEC2:
			_shader->setVec2(name, value.v2);
			break;
		case PropertyType::VEC3:
			_shader->setVec3(name, value.v3);
			break;
		case PropertyType::VEC4:
			_shader->setVec4(name, value.v4);
			break;
		case PropertyType::MAT2:
			_shader->setMat2(name, value.m2);
			break;
		case PropertyType::MAT3:
			_shader->setMat3(name, value.m3);
			break;
		case PropertyType::MAT4:
			_shader->setMat4(name, value.m4);
			break;
		case PropertyType::TEX2D:
		{
			glActiveTexture(GL_TEXTURE0 + texureIndex);
			GLint loc = glGetUniformLocation(_shader->ID, name.c_str());
			if (loc >= 0) {
				Texture2D* tex2D = static_cast<Texture2D*>(value.p);
				glUniform1i(loc, texureIndex);
				glBindTexture(GL_TEXTURE_2D, tex2D->GetID());
				++texureIndex;
			}
		}
			break;
		}

	}
}

