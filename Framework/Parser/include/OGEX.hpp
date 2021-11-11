#include <unordered_map>
#include "OpenGEX.h"
#include "portable.hpp"
#include "SceneParser.hpp"

RTR_BEGIN_NAMESPACE

class OgexParser : implements SceneParser
{
private:
	std::unordered_map<std::string, std::shared_ptr<BaseSceneObject>> m_SceneObjects;

private:
	void ConvertOddlStructureToSceneNode(const ODDL::Structure& structure, std::unique_ptr<BaseSceneNode>& base_node);

public:
	OgexParser() = default;
	virtual ~OgexParser() = default;

	virtual std::unique_ptr<BaseSceneNode> Parse(const std::string& buf);
};

RTR_END_NAMESPACE