// cpp文件

#include "Direct3D9TextureCache.h"

USING_NS_EDGE;

Direct3D9TextureCache::Direct3D9TextureCache()
: _textureStrKeyPool()
, _textureNumKeyPool()
{}

Direct3D9TextureCache::~Direct3D9TextureCache()
{
	clear();
}

void Direct3D9TextureCache::insertTexture(const std::string& tagName, ITexture2D* texture)
{
	assert(texture);
	assert(!getTexture(tagName));
	auto temp = (Direct3D9Texture2D*)texture;
	assert(!temp->m_bCache);
	temp->m_bCache = true;
	_textureStrKeyPool[tagName] = temp;
}

void Direct3D9TextureCache::insertTexture(int tag, ITexture2D* texture)
{
	assert(texture);
	assert(!getTexture(tag));
	auto temp = (Direct3D9Texture2D*)texture;
	temp->m_bCache = true;
	assert(!temp->m_bCache);
	_textureNumKeyPool[tag] = temp;
}

void Direct3D9TextureCache::removeTexture(const std::string& tagName)
{
	auto ite = _textureStrKeyPool.find(tagName);
	if (ite != _textureStrKeyPool.end())
	{
		delete ite->second;
		_textureStrKeyPool.erase(ite);
	}
}

void Direct3D9TextureCache::removeTexture(int tag)
{
	auto ite = _textureNumKeyPool.find(tag);
	if (ite != _textureNumKeyPool.end())
	{
		delete ite->second;
		_textureNumKeyPool.erase(ite);
	}
}

ITexture2D* Direct3D9TextureCache::getTexture(const std::string& tagName) const
{
	auto ite = _textureStrKeyPool.find(tagName);
	if (ite != _textureStrKeyPool.end())
	{
		return ite->second;
	}
	return NULL;
}

ITexture2D* Direct3D9TextureCache::getTexture(int tag) const
{
	auto ite = _textureNumKeyPool.find(tag);
	if (ite != _textureNumKeyPool.end())
	{
		return ite->second;
	}
	return NULL;
}

void Direct3D9TextureCache::clear()
{
	for (auto& pair : _textureStrKeyPool)
	{
		delete pair.second;
	}
	_textureStrKeyPool.clear();
	for (auto& pair : _textureNumKeyPool)
	{
		delete pair.second;
	}
	_textureNumKeyPool.clear();
}