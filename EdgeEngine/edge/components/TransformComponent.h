/********************************************
名称:
说明:
1.
********************************************/

#ifndef __TRANSFORM_COMPONENT_H_H__
#define __TRANSFORM_COMPONENT_H_H__

#include "Component.h"

NS_EDGE_BEGIN

class TransformComponent;

class ITransformListener
{
public:
	virtual void onPositionChange(TransformComponent* transform) = 0;
	virtual void onRotationChange(TransformComponent* transform) = 0;
	virtual void onScaleChange(TransformComponent* transform) = 0;
	virtual void onTransformRelease() = 0;
};

class EDGE_DLL TransformComponent : public Component, public ITransformListener
{
public:
	virtual void onPositionChange(TransformComponent* transform);
	virtual void onRotationChange(TransformComponent* transform);
	virtual void onScaleChange(TransformComponent* transform);
	virtual void onTransformRelease();

protected:
	TransformComponent();

public:
	static TransformComponent* create();
	static TransformComponent* create(TransformComponent* worldTransform);
	virtual ~TransformComponent();

	void setWorldTransform(TransformComponent* worldTransform);
	void setFollowWorldScaleEnable(bool b);
	void setPosition(const Vec2& position);
	void setScale(const Vec2& scale);
	void setRotationZ(float angle);

	const Vec2& getPosition() const;
	const Vec2& getScale() const;
	float getRotationZ() const;

	virtual void onEnter();
	virtual void onExit();
	virtual void onStart();

	virtual void onFastUpdate(double dt);
	virtual void onUpdate(double dt);
	virtual void onLateUpdate(double dt);
	virtual void onRender(double dt);

public:
	void addTransformListener(ITransformListener* transform);
	void removeTransformListener(ITransformListener* transform);

private:
	TransformComponent* _worldTransform;
	Vec2 _position;
	Vec2 _scale;
	float m_fRotationZ;

	Vec2 _savePosition;
	Vec2 _saveScale;
	float m_fSaveRotationZ;

	std::vector<ITransformListener*> _transformListenerList;

	bool m_bTransformChange;

	bool m_bFollowWorldScale;
};

NS_EDGE_END

#endif // __TRANSFORM_COMPONENT_H_H__