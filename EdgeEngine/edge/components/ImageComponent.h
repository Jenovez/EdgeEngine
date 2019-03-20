/********************************************
名称:
说明:
1.
********************************************/

#ifndef __IMAGE_COMPONENT_H_H__
#define __IMAGE_COMPONENT_H_H__

#include "Component.h"
#include "TransformComponent.h"

NS_EDGE_BEGIN

class ITexture2DRenderer;
class ITexture2D;

class EDGE_DLL ImageComponent : public Component, public ITransformListener
{
public:
	static ImageComponent* create();
	static ImageComponent* create(const std::string& filename);
	static ImageComponent* create(int cacheTag, const Data& data);

	virtual ~ImageComponent();

	bool setTexture(const std::string& filename);
	bool setTexture(int cacheTag, const Data& data);
	bool setTexture(ITexture2D* texture);

	void setColor(const Color& color);
	const Color& getColor() const;

	void setRenderRect(const Rect& rect);
	const Rect& getRenderRect();

	const Size& getTextureSize() const;

public:
	virtual void onPositionChange(TransformComponent* transform);
	virtual void onRotationChange(TransformComponent* transform);
	virtual void onScaleChange(TransformComponent* transform);
	virtual void onTransformRelease();

public:
	virtual void onEnter();
	virtual void onExit();
	virtual void onStart();

	virtual void onFastUpdate(double dt);
	virtual void onUpdate(double dt);
	virtual void onLateUpdate(double dt);
	virtual void onRender(double dt);

protected:
	ImageComponent();
	bool init();

protected:
	ITexture2DRenderer* _texture2dRenderer;
	float m_fOpacity;

protected:
	TransformComponent* _gameObjectTransform;
	bool m_bTransformChange;

};

NS_EDGE_END

#endif // __IMAGE_COMPONENT_H_H__