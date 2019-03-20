// inl文件

#include "GameObject.h"

template<typename T>
T edge::GameObject::getComponent() const
{
	T ret = NULL;
	for (auto com : _componentList)
	{
		ret = dynamic_cast<T>(com);
		if (ret) { break; }
	}
	return ret;
}
template<typename T>
T edge::GameObject::getComponentByIndex(std::size_t index) const
{
	return dynamic_cast<T>(getComponentByIndex(index));
}
template<typename T>
T edge::GameObject::getComponentByName(const std::string& name) const
{
	return dynamic_cast<T>(getComponentByName(name));
}
template<typename T>
T edge::GameObject::getComponentByTag(int tag) const
{
	return dynamic_cast<T>(getComponentByTag(tag));
}

template<typename T>
T edge::GameObject::getGameObjectByIndex(std::size_t index) const
{
	return dynamic_cast<T>(getGameObjectByIndex(index));
}
template<typename T>
T edge::GameObject::getGameObjectByName(const std::string& name) const
{
	return dynamic_cast<T>(getGameObjectByName(name));
}
template<typename T>
T edge::GameObject::getGameObjectByTag(int tag) const
{
	return dynamic_cast<T>(getGameObjectByTag(tag));
}
