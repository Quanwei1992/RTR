#pragma once
#include "Interface.hpp"
#include "Image.hpp"
#include "Buffer.hpp"

RTR_BEGIN_NAMESPACE

Interface ImageParser
{
public:
	virtual Image Parse(const Buffer & buf) = 0;
};

RTR_END_NAMESPACE