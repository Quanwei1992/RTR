#pragma once
#include <memory>
#include <string>
#include "Interface.hpp"
#include "SceneNode.hpp"

RTR_BEGIN_NAMESPACE

Interface SceneParser
{
public:
	virtual std::unique_ptr<BaseSceneNode> Parse(const std::string & buf) = 0;
};

RTR_END_NAMESPACE


