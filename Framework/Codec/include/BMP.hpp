#pragma once

#include "ImageParser.hpp"

#include <iostream>

RTR_BEGIN_NAMESPACE


class BmpParser : implements ImageParser
{
public:
	virtual Image Parse(const Buffer& buf);
};

RTR_END_NAMESPACE