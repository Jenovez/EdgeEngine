/********************************************
名称:PoolManager 池管理器
说明:
1.
********************************************/

#ifndef __POOL_MANAGER_H_H__
#define __POOL_MANAGER_H_H__

#include "CommonConfig.h"

NS_EDGE_BEGIN

class AutoReleasePool;
class Object;

class EDGE_DLL PoolManager final
{
public:
	/**
	* 添加对象到默认池中
	*/
	static void pushToDefaultPool(Object* obj);
	/**
	* 添加对象到粒子池中
	*/
	static void pushToParticlPool(Object* obj);
	/**
	* 添加对象到自定义池中
	* 参数1:指定的池的名称
	*/
	static void pushToCustomPool(const std::string& poolName, Object* obj);
	/**
	* 所有池update
	*/
	static void update();

	// 获得默认池
	static AutoReleasePool& getDefaultPool();
	// 获得粒子池
	static AutoReleasePool& getParticlePool();
	// 获得自定义池
	static AutoReleasePool& getCustomPool(const std::string& poolName);

private:
	static AutoReleasePool _defaultPool; // 默认池
	static AutoReleasePool _particlePool; // 粒子池
	static std::map<std::string, AutoReleasePool> _customPoolList; // 自定义池
};

NS_EDGE_END

#endif // __POOL_MANAGER_H_H__