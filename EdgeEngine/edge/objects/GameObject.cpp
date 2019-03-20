// cpp文件

#include "GameObject.h"
#include <components/Component.h>
#include <base/Schedule.h>
#include <components/TransformComponent.h>

USING_NS_EDGE;

bool compareGameObjectWithZOrder(GameObject* o1, GameObject* o2)
{
	return o1->getZOrder() < o2->getZOrder();
}
bool compareComponentWithZOrder(Component* o1, Component* o2)
{
	return o1->getZOrder() < o2->getZOrder();
}
bool compareScheduleWithZOrder(Schedule* s1, Schedule* s2)
{
	return s1->getZOrder() < s2->getZOrder();
}

GameObject* GameObject::create()
{
	auto obj = new GameObject();
	obj->autorelease();
	return obj;
}

GameObject::GameObject()
: _componentList()
, _gameObjectList()
, _parentGameObject(NULL)
, m_iZOrder(0)
, _anchorPoint(Vec2(0.5, 0.5))
, _scheduleList()
, _transform(NULL)
, m_bSortComponents(false)
, m_bSortGameObjects(false)
, m_bSortSchedule(false)
, m_bActive(true)
, m_bUpdate(true)
, m_bRender(true)
, m_bStart(false)
{
	_transform = TransformComponent::create();
	_transform->_gameObject = this;
	_transform->retain();
}

GameObject::~GameObject()
{
	removeAllComponents();
	removeAllGameObjects();
	removeAllSchedule();
	_transform->_gameObject = NULL;
	_transform->release();
}

void GameObject::setAnchorPoint(const Vec2& point) { _anchorPoint = point; }
const Vec2& GameObject::getAnchorPoint() const { return _anchorPoint; }

// ======================================================
// components
// ======================================================
void GameObject::addComponent(Component* com)
{
	if (!com) { return; }
	if (com->_gameObject) { return; }
	com->_gameObject = this;
	if (_componentAddTempList.empty())
	{
		_componentAddTempList.reserve(4);
	}
	_componentAddTempList.push_back(com);
	com->retain();
	com->onEnter();
	m_bSortComponents = true;
}
void GameObject::addComponent(Component* com, int zOrder)
{
	if (!com) { return; }
	com->m_iZOrder = zOrder;
	addComponent(com);
}
void GameObject::removeComponent(Component* com)
{
	if (!com) { return; }
	auto ite = std::find(_componentList.begin(), _componentList.end(), com);
	if (ite != _componentList.end())
	{
		com->onExit();
		com->_gameObject = NULL;
		com->release();
		_componentList.erase(ite);
	}
}
void GameObject::removeComponentByIndex(std::size_t index)
{
	removeComponent(getComponentByIndex(index));
}
void GameObject::removeComponentByName(const std::string& name)
{
	if (name == "") { return; }
	auto ite = _componentList.begin();
	while (ite != _componentList.end())
	{
		if ((*ite)->getName() == name)
		{
			(*ite)->onExit();
			(*ite)->_gameObject = NULL;
			(*ite)->release();
			_componentList.erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeComponentByTag(int tag)
{
	auto ite = _componentList.begin();
	while (ite != _componentList.end())
	{
		if ((*ite)->getTag() == tag)
		{
			(*ite)->onExit();
			(*ite)->_gameObject = NULL;
			(*ite)->release();
			_componentList.erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeAllComponents()
{
	for (auto com : _componentList)
	{
		com->onExit();
		com->_gameObject = NULL;
		com->release();
	}
	_componentList.clear();
}
const std::vector<Component*>& GameObject::getComponentList() const { return _componentList; }
void GameObject::sortAllComponents()
{
	std::sort(_componentList.begin(), _componentList.end(), compareComponentWithZOrder);
}
Component* GameObject::getComponentByIndex(std::size_t index) const
{
	if (index < _componentList.size())
	{
		return _componentList[index];
	}
	return NULL;
}
Component* GameObject::getComponentByName(const std::string& name) const
{
	auto ite = _componentList.begin();
	while (ite != _componentList.end())
	{
		if ((*ite)->getName() == name)
		{
			return *ite;
		}
		++ite;
	}
	return NULL;
}
Component* GameObject::getComponentByTag(int tag) const
{
	auto ite = _componentList.begin();
	while (ite != _componentList.end())
	{
		if ((*ite)->getTag() == tag)
		{
			return *ite;
		}
		++ite;
	}
	return NULL;
}
void GameObject::setSortComponentsEnable(bool b) { m_bSortComponents = b; }

// ========================================================
// gameobject
// ========================================================
void GameObject::addGameObject(GameObject* obj)
{
	if (!obj) { return; }
	if (obj->_parentGameObject) { return; }
	obj->_parentGameObject = this;
	obj->_transform->setWorldTransform(_transform);
	if (_gameObjectAddTempList.empty())
	{
		_gameObjectAddTempList.reserve(4);
	}
	_gameObjectAddTempList.push_back(obj);
	obj->retain();
	obj->onEnter();
	m_bSortGameObjects = true;
}
void GameObject::addGameObject(GameObject* obj, int zOrder)
{
	if (!obj) { return; }
	obj->m_iZOrder = zOrder;
	addGameObject(obj);
}
void GameObject::removeGameObject(GameObject* obj)
{
	if (!obj) { return; }
	auto ite = std::find(_gameObjectList.begin(), _gameObjectList.end(), obj);
	if (ite != _gameObjectList.end())
	{
		obj->onExit();
		obj->_parentGameObject = NULL;
		obj->_transform->setWorldTransform(NULL);
		obj->release();
		_gameObjectList.erase(ite);
	}
}
void GameObject::removeGameObjectByIndex(std::size_t index)
{
	removeGameObject(getGameObjectByIndex(index));
}
void GameObject::removeGameObjectByName(const std::string& name)
{
	if (name == "") { return; }
	auto ite = _gameObjectList.begin();
	while (ite != _gameObjectList.end())
	{
		if ((*ite)->getName() == name)
		{
			(*ite)->onExit();
			(*ite)->_parentGameObject = NULL;
			(*ite)->release();
			_gameObjectList.erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeGameObjectByTag(int tag)
{
	auto ite = _gameObjectList.begin();
	while (ite != _gameObjectList.end())
	{
		if ((*ite)->getTag() == tag)
		{
			(*ite)->onExit();
			(*ite)->_parentGameObject = NULL;
			(*ite)->release();
			_gameObjectList.erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeAllGameObjects()
{
	for (auto obj : _gameObjectList)
	{
		obj->onExit();
		obj->_parentGameObject = NULL;
		obj->release();
	}
	_gameObjectList.clear();
}
const std::vector<GameObject*>& GameObject::getGameObjectList() const { return _gameObjectList; }
void GameObject::sortAllGameObjects()
{
	std::sort(_gameObjectList.begin(), _gameObjectList.end(), compareGameObjectWithZOrder);
}
GameObject* GameObject::getGameObjectByIndex(std::size_t index) const
{
	if (index < _gameObjectList.size())
	{
		return _gameObjectList[index];
	}
	return NULL;
}
GameObject* GameObject::getGameObjectByName(const std::string& name) const
{
	auto ite = _gameObjectList.begin();
	while (ite != _gameObjectList.end())
	{
		if ((*ite)->getName() == name)
		{
			return *ite;
		}
		++ite;
	}
	return NULL;
}
GameObject* GameObject::getGameObjectByTag(int tag) const
{
	auto ite = _gameObjectList.begin();
	while (ite != _gameObjectList.end())
	{
		if ((*ite)->getTag() == tag)
		{
			return *ite;
		}
		++ite;
	}
	return NULL;
}
GameObject* GameObject::getParentGameObject() const
{
	return _parentGameObject;
}
void GameObject::removeFromParent()
{
	if (_parentGameObject)
	{
		_parentGameObject->removeGameObject(this);
		_parentGameObject = NULL;
	}
}

int GameObject::getZOrder() const { return m_iZOrder; }
void GameObject::setZOrder(int order)
{
	if (m_iZOrder != order)
	{
		m_iZOrder = order;
		if (_parentGameObject)
		{
			_parentGameObject->m_bSortGameObjects = true;
		}
	}
}
void GameObject::setSortGameObjectsEnable(bool b) { m_bSortGameObjects = b; }

void GameObject::onEnter()
{}
void GameObject::onExit()
{}
void GameObject::onStart()
{}
// =========================================================

void GameObject::updateFastSchedule(double dt)
{
	if (!_gameObjectAddTempList.empty())
	{
		_gameObjectList.insert(_gameObjectList.end(), _gameObjectAddTempList.begin(), _gameObjectAddTempList.end());
		_gameObjectAddTempList.clear();
	}
	if (!_componentAddTempList.empty())
	{
		_componentList.insert(_componentList.end(), _componentAddTempList.begin(), _componentAddTempList.end());
		_componentAddTempList.clear();
	}

	if (m_bSortGameObjects)
	{
		sortAllGameObjects();
		m_bSortGameObjects = false;
	}
	if (m_bSortComponents)
	{
		sortAllComponents();
		m_bSortComponents = false;
	}
	if (m_bSortSchedule)
	{
		sortAllSchedule();
		m_bSortSchedule = false;
	}

	if (!m_bActive) { return; }
	if (!m_bUpdate) { return; }

	std::vector<Schedule*> scheduleTempList(_scheduleList[UpdateType::FAST_UPDATE]);
	for (auto sche : scheduleTempList)
	{
		sche->retain();
		sche->update(dt);
		sche->release();
		if (sche->isStop())
		{
			removeSchedule(UpdateType::FAST_UPDATE, sche);
		}
	}

	_transform->onFastUpdate(dt);
	std::vector<Component*> componentTempList(_componentList);
	for (auto com : componentTempList)
	{
		com->retain();
		if (!com->m_bStart)
		{
			com->onStart();
			com->m_bStart = true;
		}
		com->onFastUpdate(dt);
		com->release();
	}
	std::vector<GameObject*> gameobjectTempList(_gameObjectList);
	for (auto obj : gameobjectTempList)
	{
		obj->retain();
		if (!obj->m_bStart)
		{
			obj->onStart();
			obj->m_bStart = true;
		}
		obj->updateFastSchedule(dt);
		obj->release();
	}
}
void GameObject::updateNormalSchedule(double dt)
{
	if (!m_bActive) { return; }
	if (!m_bUpdate) { return; }

	std::vector<Schedule*> scheduleTempList(_scheduleList[UpdateType::NORMAL_UPDATE]);
	for (auto sche : scheduleTempList)
	{
		sche->retain();
		sche->update(dt);
		sche->release();
		if (sche->isStop())
		{
			removeSchedule(UpdateType::NORMAL_UPDATE, sche);
		}
	}

	_transform->onUpdate(dt);
	std::vector<Component*> componentTempList(_componentList);
	for (auto com : componentTempList)
	{
		com->retain();
		com->onUpdate(dt);
		com->release();
	}
	std::vector<GameObject*> gameobjectTempList(_gameObjectList);
	for (auto obj : gameobjectTempList)
	{
		obj->retain();
		obj->updateNormalSchedule(dt);
		obj->release();
	}
}
void GameObject::updateLateSchedule(double dt)
{
	if (!m_bActive) { return; }
	if (!m_bUpdate) { return; }

	std::vector<Schedule*> scheduleTempList(_scheduleList[UpdateType::LATE_UPDATE]);
	for (auto sche : scheduleTempList)
	{
		sche->retain();
		sche->update(dt);
		sche->release();
		if (sche->isStop())
		{
			removeSchedule(UpdateType::LATE_UPDATE, sche);
		}
	}

	_transform->onLateUpdate(dt);
	std::vector<Component*> componentTempList(_componentList);
	for (auto com : componentTempList)
	{
		com->retain();
		com->onLateUpdate(dt);
		com->release();
	}
	std::vector<GameObject*> gameobjectTempList(_gameObjectList);
	for (auto obj : gameobjectTempList)
	{
		obj->retain();
		obj->updateLateSchedule(dt);
		obj->release();
	}
}
void GameObject::updateRenderSchedule(double dt)
{
	if (!m_bActive) { return; }
	if (!m_bRender) { return; }

	std::vector<Schedule*> scheduleTempList(_scheduleList[UpdateType::RENDER_UPDATE]);
	for (auto sche : scheduleTempList)
	{
		sche->retain();
		sche->update(dt);
		sche->release();
		if (sche->isStop())
		{
			removeSchedule(UpdateType::RENDER_UPDATE, sche);
		}
	}

	_transform->onRender(dt);
	std::vector<Component*> componentTempList(_componentList);
	for (auto com : componentTempList)
	{
		com->retain();
		com->onRender(dt);
		com->release();
	}
	std::vector<GameObject*> gameobjectTempList(_gameObjectList);
	for (auto obj : gameobjectTempList)
	{
		obj->retain();
		obj->updateRenderSchedule(dt);
		obj->release();
	}
}

// ========================================================
// schedule
// ========================================================
void GameObject::addSchedule(UpdateType type, Schedule* schedule)
{
	if (!schedule) { return; }
	schedule->retain();
	setSortScheduleEnable(true);
	_scheduleList[type].push_back(schedule);
}
void GameObject::addSchedule(UpdateType type, Schedule* schedule, int zOrder)
{
	if (!schedule) { return; }
	schedule->setZOrder(zOrder);
	addSchedule(type, schedule);
}
void GameObject::removeSchedule(Schedule* schedule)
{
	if (!schedule) { return; }
	auto ite = _scheduleList.begin();
	while (ite != _scheduleList.end())
	{
		auto findIte = std::find(ite->second.begin(), ite->second.end(), schedule);
		if (findIte != ite->second.end())
		{
			schedule->release();
			ite->second.erase(findIte);
		}

		++ite;
	}
}
void GameObject::removeSchedule(UpdateType type, Schedule* schedule)
{
	auto ite = std::find(_scheduleList[type].begin(), _scheduleList[type].end(), schedule);
	if (ite != _scheduleList[type].end())
	{
		(*ite)->release();
		_scheduleList[type].erase(ite);
	}
}
void GameObject::removeScheduleByIndex(UpdateType type, std::size_t index)
{
	if (index < _scheduleList[type].size())
	{
		auto ite = _scheduleList[type].begin() + index;
		(*ite)->release();
		_scheduleList[type].erase(ite);
	}
}
void GameObject::removeScheduleByName(UpdateType type, const std::string& name)
{
	if (name == "") { return; }
	auto ite = _scheduleList[type].begin();
	while (ite != _scheduleList[type].end())
	{
		if ((*ite)->getName() == name)
		{
			(*ite)->release();
			_scheduleList[type].erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeScheduleByTag(UpdateType type, int tag)
{
	auto ite = _scheduleList[type].begin();
	while (ite != _scheduleList[type].end())
	{
		if ((*ite)->getTag() == tag)
		{
			(*ite)->release();
			_scheduleList[type].erase(ite);
			return;
		}
		++ite;
	}
}
void GameObject::removeAllSchedule(UpdateType type)
{
	for (auto sche : _scheduleList[type])
	{
		sche->release();
	}
	_scheduleList[type].clear();
}
void GameObject::removeAllSchedule()
{
	for (auto& pair : _scheduleList)
	{
		for (auto sc : pair.second)
		{
			sc->release();
		}
	}
	_scheduleList.clear();
}
std::vector<Schedule*>& GameObject::getScheduleList(UpdateType type) { return _scheduleList[type]; }
void GameObject::sortAllSchedule()
{
	for (auto& pair : _scheduleList)
	{
		std::sort(pair.second.begin(), pair.second.end(), compareScheduleWithZOrder);
	}
}
Schedule* GameObject::getScheduleByIndex(UpdateType type, std::size_t index) const
{
	if (_scheduleList.find(type) == _scheduleList.end()) { return nullptr; }
	if (index < _scheduleList.at(type).size())
	{
		return _scheduleList.at(type)[index];
	}
	return NULL;
}
Schedule* GameObject::getScheduleByName(UpdateType type, const std::string& name) const
{
	if (_scheduleList.find(type) == _scheduleList.end()) { return nullptr; }
	for (auto s : _scheduleList.at(type))
	{
		if (s->getName() == name)
		{
			return s;
		}
	}
	return NULL;
}
Schedule* GameObject::getScheduleByTag(UpdateType type, int tag) const
{
	if (_scheduleList.find(type) == _scheduleList.end()) { return nullptr; }
	for (auto s : _scheduleList.at(type))
	{
		if (s->getTag() == tag)
		{
			return s;
		}
	}
	return NULL;
}
void GameObject::setSortScheduleEnable(bool b) { m_bSortSchedule = b; }
TransformComponent* GameObject::getTransformComponent() const { return _transform; }
// ========================================================
void GameObject::setActiveEnable(bool b) { m_bActive = b; }
void GameObject::setUpdateEnable(bool b) { m_bUpdate = b; }
void GameObject::setRenderEnable(bool b) { m_bRender = b; }
bool GameObject::isActiveEnable() const { return m_bActive; }
bool GameObject::isUpdateEnable() const { return m_bUpdate; }
bool GameObject::isRenderEnable() const { return m_bRender; }
// ========================================================
