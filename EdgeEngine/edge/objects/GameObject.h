/********************************************
名称:GameObject 游戏对象
说明:
1.通过添加组件来完成功能
2.通过添加子对象来完成对象和对象之间的相互关系
3.通过添加计时器来添加自定义的update方法
********************************************/

#ifndef __GAME_OBJECT_H_H__
#define __GAME_OBJECT_H_H__

#include <base/Object.h>

NS_EDGE_BEGIN

class Component;
class Schedule;

class TransformComponent;

class EDGE_DLL GameObject : public Object
{
public:
	static GameObject* create();
	virtual ~GameObject();

public:
	virtual void setAnchorPoint(const Vec2& point) final;
	virtual const Vec2& getAnchorPoint() const final;

public:
	virtual void addComponent(Component* com) final;
	virtual void addComponent(Component* com, int zOrder) final;
	virtual void removeComponent(Component* com) final;
	virtual void removeComponentByIndex(std::size_t index) final;
	virtual void removeComponentByName(const std::string& name) final;
	virtual void removeComponentByTag(int tag) final;
	virtual void removeAllComponents() final;
	virtual const std::vector<Component*>& getComponentList() const final;
	virtual void sortAllComponents() final;
	virtual Component* getComponentByIndex(std::size_t index) const final;
	virtual Component* getComponentByName(const std::string& name) const final;
	virtual Component* getComponentByTag(int tag) const final;

	template<typename T>
	T getComponent() const;
	template<typename T>
	T getComponentByIndex(std::size_t index) const;
	template<typename T>
	T getComponentByName(const std::string& name) const;
	template<typename T>
	T getComponentByTag(int tag) const;

	virtual void setSortComponentsEnable(bool b) final;

public:
	virtual void addGameObject(GameObject* obj) final;
	virtual void addGameObject(GameObject* obj, int zOrder) final;
	virtual void removeGameObject(GameObject* obj) final;
	virtual void removeGameObjectByIndex(std::size_t index) final;
	virtual void removeGameObjectByName(const std::string& name) final;
	virtual void removeGameObjectByTag(int tag) final;
	virtual void removeAllGameObjects() final;
	virtual const std::vector<GameObject*>& getGameObjectList() const final;
	virtual void sortAllGameObjects() final;
	virtual GameObject* getGameObjectByIndex(std::size_t index) const final;
	virtual GameObject* getGameObjectByName(const std::string& name) const final;
	virtual GameObject* getGameObjectByTag(int tag) const final;

	template<typename T>
	T getGameObjectByIndex(std::size_t index) const;
	template<typename T>
	T getGameObjectByName(const std::string& name) const;
	template<typename T>
	T getGameObjectByTag(int tag) const;

	virtual GameObject* getParentGameObject() const final;
	virtual void removeFromParent() final;

	virtual void setZOrder(int order) final;
	virtual int getZOrder() const final;
	virtual void setSortGameObjectsEnable(bool b) final;

	virtual void onEnter();
	virtual void onExit();
	virtual void onStart();

public:
	virtual void updateFastSchedule(double dt) final;
	virtual void updateNormalSchedule(double dt) final;
	virtual void updateLateSchedule(double dt) final;
	virtual void updateRenderSchedule(double dt) final;

	virtual void addSchedule(UpdateType type, Schedule* schedule) final;
	virtual void addSchedule(UpdateType type, Schedule* schedule, int zOrder) final;
	virtual void removeSchedule(Schedule* schedule) final;
	virtual void removeSchedule(UpdateType type, Schedule* schedule) final;
	virtual void removeScheduleByIndex(UpdateType type, std::size_t index) final;
	virtual void removeScheduleByName(UpdateType type, const std::string& name) final;
	virtual void removeScheduleByTag(UpdateType type, int tag) final;
	virtual void removeAllSchedule(UpdateType type) final;
	virtual void removeAllSchedule() final;
	virtual std::vector<Schedule*>& getScheduleList(UpdateType type) final;
	virtual void sortAllSchedule() final;
	virtual Schedule* getScheduleByIndex(UpdateType type, std::size_t index) const final;
	virtual Schedule* getScheduleByName(UpdateType type, const std::string& name) const final;
	virtual Schedule* getScheduleByTag(UpdateType type, int tag) const final;
	virtual void setSortScheduleEnable(bool b) final;

public:
	virtual TransformComponent* getTransformComponent() const;

public:
	virtual void setActiveEnable(bool b) final;
	virtual void setUpdateEnable(bool b) final;
	virtual void setRenderEnable(bool b) final;
	virtual bool isActiveEnable() const final;
	virtual bool isUpdateEnable() const final;
	virtual bool isRenderEnable() const final;

protected:
	GameObject();

private:
	std::vector<Component*> _componentList; // 组件列表
	std::vector<Component*> _componentAddTempList; // 组件临时列表(确保任何组件都必须从1开始执行)
	std::vector<GameObject*> _gameObjectList; // 子对象列表
	std::vector<GameObject*> _gameObjectAddTempList; // 子对象临时列表
	GameObject* _parentGameObject; // 父对象,若没有则为NULL

	int m_iZOrder; // 排序值
	Vec2 _anchorPoint; // 锚点

	std::map<UpdateType, std::vector<Schedule*>> _scheduleList; // 计时器列表

private:
	TransformComponent* _transform;

private:
	bool m_bSortComponents; // 是否排序组件列表
	bool m_bSortGameObjects; // 是否排序子对象列表
	bool m_bSortSchedule; // 是否排序计时器列表

	bool m_bActive; // 是否激活
	bool m_bUpdate; // 是否update
	bool m_bRender; // 是否渲染
	bool m_bStart; // 是否开始执行(第一次执行FastUpdate)
};

NS_EDGE_END

#include "GameObject.inl"

#endif // __GAME_OBJECT_H_H__