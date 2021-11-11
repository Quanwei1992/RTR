#include "SceneObject.hpp"

RTR_BEGIN_NAMESPACE

float RTR::DefaultAttenFunc(float intensity, float distance)
{
	return intensity / (1 + distance);
}

std::ostream& operator<<(std::ostream& out, SceneObjectType type)
{
	int32_t n = static_cast<int32_t>(type);
	n = endian_net_unsigned_int<int32_t>(n);
	char* c = reinterpret_cast<char*>(&n);

	for (size_t i = 0; i < sizeof(int32_t); i++) {
		out << *c++;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, VertexDataType type)
{
	int32_t n = static_cast<int32_t>(type);
	n = endian_net_unsigned_int<int32_t>(n);
	char* c = reinterpret_cast<char*>(&n);

	for (size_t i = 0; i < sizeof(int32_t); i++) {
		out << *c++;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, IndexDataType type)
{
	int32_t n = static_cast<int32_t>(type);
	n = endian_net_unsigned_int<int32_t>(n);
	char* c = reinterpret_cast<char*>(&n);

	for (size_t i = 0; i < sizeof(int32_t); i++) {
		out << *c++;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, PrimitiveType type)
{
	int32_t n = static_cast<int32_t>(type);
	n = endian_net_unsigned_int<int32_t>(n);
	char* c = reinterpret_cast<char*>(&n);

	for (size_t i = 0; i < sizeof(int32_t); i++) {
		out << *c++;
	}

	return out;
}

RTR_END_NAMESPACE

