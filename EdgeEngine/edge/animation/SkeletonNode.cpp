// cpp文件

#include "SkeletonNode.h"
#include <renderer/RendererManager.h>

USING_NS_EDGE;

SkeletonNode::SkeletonNode()
	: m_sName("")
	, _textureRenderer(NULL)
	, _anchorPoint(Vec2(0.5, 0.5))
	, _transform(NULL)
	, _parentNode(NULL)
	, _nextNodeList()
{
	_transform = TransformComponent::create();
	_transform->setFollowWorldScaleEnable(false);
	_transform->retain();

	_textureRenderer = RendererManager::getInstance()->createTexture2DRenderer();
}

SkeletonNode::~SkeletonNode()
{
	SAFE_DELETE(_textureRenderer);
	removeAllSkeletonNode();
	_transform->release();
}

void SkeletonNode::update(double dt)
{
	_transform->onFastUpdate(dt);
	_transform->onUpdate(dt);
	_transform->onLateUpdate(dt);

	_textureRenderer->setAnchorPoint(getAnchorPoint());
	_textureRenderer->setTransform(getPosition(), getScale(), getRotationZ());

	for (auto& pair : _nextNodeList)
	{
		pair.second->update(dt);
	}
}

void SkeletonNode::render(double dt)
{
	_transform->onRender(dt);

	_textureRenderer->draw();

	for (auto& pair : _nextNodeList)
	{
		pair.second->render(dt);
	}
}

void SkeletonNode::setName(const std::string& name) { m_sName = name; }
const std::string& SkeletonNode::getName() const { return m_sName; }
void SkeletonNode::setTexture(ITexture2D* texture)
{
	_textureRenderer->setTexture(texture);
	_textureRenderer->setColor(Color::RED);
}

void SkeletonNode::setAnchorPoint(const Vec2& anchor)
{
	_anchorPoint = anchor;
}
void SkeletonNode::setPosition(const Vec2& position)
{
	_transform->setPosition(position);
}
void SkeletonNode::setScale(const Vec2& scale)
{
	_transform->setScale(scale);
}
void SkeletonNode::setRotationZ(float angle)
{
	_transform->setRotationZ(angle);
}

const Vec2& SkeletonNode::getAnchorPoint() const { return _anchorPoint; }
const Vec2& SkeletonNode::getPosition() const { return _transform->getPosition(); }
const Vec2& SkeletonNode::getScale() const { return _transform->getScale(); }
float SkeletonNode::getRotationZ() const { return _transform->getRotationZ(); }

void SkeletonNode::insertSkeletonNode(const std::string& name, SkeletonNode* node)
{
	assert(node && (node != this) && (!node->_parentNode));

	if (node && (node != this) && (!node->_parentNode))
	{
		node->setName(name);
		node->_parentNode = this;
		node->_transform->setWorldTransform(_transform);
		_nextNodeList.insert(std::make_pair(name, node));
	}
}

void SkeletonNode::removeSkeletonNode(SkeletonNode* node)
{
	removeSkeletonNode(node->getName());
}
void SkeletonNode::removeSkeletonNode(const std::string& name)
{
	auto ite = _nextNodeList.find(name);
	if (ite != _nextNodeList.end())
	{
		delete ite->second;
		_nextNodeList.erase(ite);
	}
}

void SkeletonNode::removeAllSkeletonNode()
{
	for (auto& pair : _nextNodeList)
	{
		delete pair.second;
	}
	_nextNodeList.clear();
}

SkeletonNode* SkeletonNode::getSkeletonNodeByName(const std::string& name) const
{
	auto ite = _nextNodeList.find(name);
	if (ite != _nextNodeList.end())
	{
		return ite->second;
	}
	return NULL;
}

SkeletonNode* SkeletonNode::getSkeletonNodeByNameSearchChildren(const std::string& name) const
{
	auto current = getSkeletonNodeByName(name);
	if (current) { return current; }
	for (auto& pair : _nextNodeList)
	{
		current = pair.second->getSkeletonNodeByNameSearchChildren(name);
		if (current) { return current; }
	}
	return NULL;
}
SkeletonNode* SkeletonNode::getParentNode() const { return _parentNode; }
