// cpp文件

#include "PoolManager.h"
#include "AutoReleasePool.h"

USING_NS_EDGE;

AutoReleasePool PoolManager::_defaultPool;
AutoReleasePool PoolManager::_particlePool;
std::map<std::string, AutoReleasePool> PoolManager::_customPoolList;

void PoolManager::pushToDefaultPool(Object* obj)
{
	_defaultPool.push(obj);
}

void PoolManager::pushToParticlPool(Object* obj)
{
	_particlePool.push(obj);
}

void PoolManager::pushToCustomPool(const std::string& poolName, Object* obj)
{
	_customPoolList[poolName].push(obj);
}

void PoolManager::update()
{
	_defaultPool.update();
	_particlePool.update();
	for (auto& pair : _customPoolList)
	{
		pair.second.update();
	}
}

AutoReleasePool& PoolManager::getDefaultPool() { return _defaultPool; }
AutoReleasePool& PoolManager::getParticlePool() { return _particlePool; }
AutoReleasePool& PoolManager::getCustomPool(const std::string& poolName) { return _customPoolList[poolName]; }