#pragma once

#include "geommath.hpp"

RTR_BEGIN_NAMESPACE

typedef struct _Image
{
	uint32_t Width;
	uint32_t Height;
	R8G8B8A8Unorm* data;
	uint32_t bitcount;
	uint32_t pitch;
	size_t data_size;
} Image;

RTR_END_NAMESPACE