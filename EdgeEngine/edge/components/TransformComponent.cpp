// cpp文件

#include "TransformComponent.h"

USING_NS_EDGE;

TransformComponent::TransformComponent()
	: _worldTransform(NULL)
	, _position()
	, _scale(1, 1)
	, m_fRotationZ(0)
	, _savePosition()
	, _saveScale(1, 1)
	, m_fSaveRotationZ(0)
	, m_bTransformChange(true)
	, m_bFollowWorldScale(true)
{}

TransformComponent* TransformComponent::create()
{
	auto ret = new TransformComponent();
	ret->autorelease();
	return ret;
}
TransformComponent* TransformComponent::create(TransformComponent* worldTransform)
{
	auto ret = new TransformComponent();
	ret->setWorldTransform(worldTransform);
	ret->autorelease();
	return ret;
}


TransformComponent::~TransformComponent()
{
	if (_worldTransform)
	{
		_worldTransform->removeTransformListener(this);
	}
	for (auto listener : _transformListenerList)
	{
		listener->onTransformRelease();
	}
}

void TransformComponent::onPositionChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void TransformComponent::onRotationChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void TransformComponent::onScaleChange(TransformComponent* transform)
{
	m_bTransformChange = true;
}

void TransformComponent::onTransformRelease()
{
	_worldTransform = NULL;
	m_bTransformChange = true;
}

void TransformComponent::setWorldTransform(TransformComponent* worldTransform)
{
	if (_worldTransform)
	{
		_worldTransform->removeTransformListener(this);
	}
	_worldTransform = worldTransform;
	if (_worldTransform)
	{
		_worldTransform->addTransformListener(this);
	}
	m_bTransformChange = true;
}
void TransformComponent::setFollowWorldScaleEnable(bool b) { m_bFollowWorldScale = b; }
void TransformComponent::setPosition(const Vec2& position)
{
	_savePosition = position;
	for (auto listener : _transformListenerList)
	{
		listener->onPositionChange(this);
	}
}
void TransformComponent::setScale(const Vec2& scale)
{
	_saveScale = scale;
	for (auto listener : _transformListenerList)
	{
		listener->onScaleChange(this);
	}
}
void TransformComponent::setRotationZ(float angle)
{
	m_fSaveRotationZ = angle;
	for (auto listener : _transformListenerList)
	{
		listener->onRotationChange(this);
	}
}
const Vec2& TransformComponent::getPosition() const { return _position; }
const Vec2& TransformComponent::getScale() const { return _scale; }
float TransformComponent::getRotationZ() const { return m_fRotationZ; }

void TransformComponent::onEnter()
{}

void TransformComponent::onExit()
{}

void TransformComponent::onStart()
{}

void TransformComponent::onFastUpdate(double dt)
{
	if (m_bTransformChange)
	{
		if (_worldTransform)
		{
			m_fRotationZ = m_fSaveRotationZ + _worldTransform->m_fRotationZ;
			if (m_bFollowWorldScale)
			{
				_scale = _saveScale * _worldTransform->_scale;
			}
			else
			{
				_scale = _saveScale;
			}
			double length = (float)_savePosition.length();
			float angleF = (float)((double)_worldTransform->m_fRotationZ / 180.0 * MATH_PI) + atan2f((float)_savePosition.y, (float)_savePosition.x);
			double x = cosf(angleF) * length + _worldTransform->_position.x;
			double y = sinf(angleF) * length + _worldTransform->_position.y;
			_position.setValue(x, y);
		}
		else
		{
			m_fRotationZ = m_fSaveRotationZ;
			_scale = _saveScale;
			_position = _savePosition;
		}
		m_bTransformChange = false;
	}
}

void TransformComponent::onUpdate(double dt)
{
}

void TransformComponent::onLateUpdate(double dt)
{}

void TransformComponent::onRender(double dt)
{
}

void TransformComponent::addTransformListener(ITransformListener* transform)
{
	if (transform)
	{
		_transformListenerList.push_back(transform);
	}
}

void TransformComponent::removeTransformListener(ITransformListener* transform)
{
	auto ite = std::find(_transformListenerList.begin(), _transformListenerList.end(), transform);
	if (ite != _transformListenerList.end())
	{
		_transformListenerList.erase(ite);
	}
}
