// cpp文件

#include "AutoReleasePool.h"
#include "Object.h"

USING_NS_EDGE;

AutoReleasePool::AutoReleasePool()
: _objectList()
{}

AutoReleasePool::~AutoReleasePool()
{
}

void AutoReleasePool::push(Object* obj)
{
	for (auto& o : _objectList)
	{
		if (o == NULL)
		{
			o = obj;
			return;
		}
	}
	_objectList.push_back(obj);
}

bool AutoReleasePool::isExist(Object* obj)
{
	auto ite = std::find(_objectList.begin(), _objectList.end(), obj);
	return (ite != _objectList.end());
}

void AutoReleasePool::update()
{
	for (auto& obj : _objectList)
	{
		if (!obj) { continue; }
		std::size_t ref = obj->getReferenceCounts();
		obj->release();
		if (ref == 1)
		{
			obj = NULL;
		}
		else
		{
			obj->retain();
		}
	}
}

void AutoReleasePool::clear()
{
	bool ret = true;
	while (ret)
	{
		ret = false;
		for (auto& obj : _objectList)
		{
			if (!obj) { continue; }
			std::size_t ref = obj->getReferenceCounts();
			obj->release();
			if (ref == 1)
			{
				obj = NULL;
			}
			else
			{
				ret = true;
			}
		}
	}
}