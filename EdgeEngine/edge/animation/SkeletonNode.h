/********************************************
名称:
说明:
1.
********************************************/

#ifndef __SKELETON_NODE_H_H__
#define __SKELETON_NODE_H_H__

#include <base/CommonConfig.h>
#include <base/EdgeTypes.h>
#include <renderer/ITexture2DRenderer.h>
#include <components/TransformComponent.h>

NS_EDGE_BEGIN

class EDGE_DLL SkeletonNode final
{
public:
	SkeletonNode();
	~SkeletonNode();

	void update(double dt);
	void render(double dt);

public:
	void setName(const std::string& name);
	const std::string& getName() const;

	void setTexture(ITexture2D* texture);

public:
	void setAnchorPoint(const Vec2& anchor);
	const Vec2& getAnchorPoint() const;
	void setPosition(const Vec2& position);
	const Vec2& getPosition() const;
	void setScale(const Vec2& scale);
	const Vec2& getScale() const;
	void setRotationZ(float angle);
	float getRotationZ() const;

public:
	void insertSkeletonNode(const std::string& name, SkeletonNode* node);
	void removeSkeletonNode(SkeletonNode* node);
	void removeSkeletonNode(const std::string& name);
	void removeAllSkeletonNode();
	SkeletonNode* getSkeletonNodeByName(const std::string& name) const;

public:
	SkeletonNode* getSkeletonNodeByNameSearchChildren(const std::string& name) const;
	SkeletonNode* getParentNode() const;

private:
	std::string m_sName;
	ITexture2DRenderer* _textureRenderer;

	Vec2 _anchorPoint;
	TransformComponent* _transform;

private:
	SkeletonNode* _parentNode;
	std::map<std::string, SkeletonNode*> _nextNodeList;
};

NS_EDGE_END

#endif // __SKELETON_NODE_H_H__