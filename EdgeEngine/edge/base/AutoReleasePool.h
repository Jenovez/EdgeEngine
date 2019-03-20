/********************************************
名称:AutoReleasePool 自动释放池
说明:
1.通过引用计数管理Object内存
********************************************/

#ifndef __AUTO_RELEASE_POOL_H_H__
#define __AUTO_RELEASE_POOL_H_H__

#include "CommonConfig.h"

NS_EDGE_BEGIN

class Object;

class EDGE_DLL AutoReleasePool final
{
public:
	AutoReleasePool();
	~AutoReleasePool();

	/**
	* 添加对象到池中
	*/
	void push(Object* obj);
	/**
	* 判断一个对象是否在池中
	*/
	bool isExist(Object* obj);
	/**
	* 检测池中对象是否已经没有引用并释放内存
	*/
	void update();
	/**
	* 清空池中的对象及其内存
	*/
	void clear();

private:
	AutoReleasePool(const AutoReleasePool&);
	AutoReleasePool& operator=(const AutoReleasePool&);

private:
	std::vector<Object*> _objectList; // 对象容器
};

NS_EDGE_END

#endif // __AUTO_RELEASE_POOL_H_H__