// cpp文件

#include "Direct2DTextureCache.h"

USING_NS_EDGE;

Direct2DTextureCache::Direct2DTextureCache()
: _textureStrKeyPool()
, _textureNumKeyPool()
{}

Direct2DTextureCache::~Direct2DTextureCache()
{
	clear();
}

void Direct2DTextureCache::insertTexture(const std::string& tagName, ITexture2D* texture)
{
	assert(texture);
	assert(!getTexture(tagName));
	auto temp = (Direct2DTexture2D*)texture;
	assert(!temp->m_bCache);
	temp->m_bCache = true;
	_textureStrKeyPool[tagName] = temp;
}

void Direct2DTextureCache::insertTexture(int tag, ITexture2D* texture)
{
	assert(texture);
	assert(!getTexture(tag));
	auto temp = (Direct2DTexture2D*)texture;
	temp->m_bCache = true;
	assert(!temp->m_bCache);
	_textureNumKeyPool[tag] = temp;
}

void Direct2DTextureCache::removeTexture(const std::string& tagName)
{
	auto ite = _textureStrKeyPool.find(tagName);
	if (ite != _textureStrKeyPool.end())
	{
		delete ite->second;
		_textureStrKeyPool.erase(ite);
	}
}

void Direct2DTextureCache::removeTexture(int tag)
{
	auto ite = _textureNumKeyPool.find(tag);
	if (ite != _textureNumKeyPool.end())
	{
		delete ite->second;
		_textureNumKeyPool.erase(ite);
	}
}

ITexture2D* Direct2DTextureCache::getTexture(const std::string& tagName) const
{
	auto ite = _textureStrKeyPool.find(tagName);
	if (ite != _textureStrKeyPool.end())
	{
		return ite->second;
	}
	return NULL;
}

ITexture2D* Direct2DTextureCache::getTexture(int tag) const
{
	auto ite = _textureNumKeyPool.find(tag);
	if (ite != _textureNumKeyPool.end())
	{
		return ite->second;
	}
	return NULL;
}

void Direct2DTextureCache::clear()
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