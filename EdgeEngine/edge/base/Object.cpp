// cpp文件

#include "Object.h"
#include "PoolManager.h"

USING_NS_EDGE;

Object::Object()
: m_iObjectID(CommonVariable::ERROR_NUMBER)
, m_sName("")
, m_iTag(0)
, m_iReferenceCounts(1)
, _numberVariableMap()
, _stringVariableMap()
, _errorCodeStr(CommonVariable::ERROR_STRING)
, m_bAutoreleaseEnable(false)
{
}

Object::~Object()
{}

void Object::setObjectID(int id) { m_iObjectID = id; }
int Object::getObjectID() const { return m_iObjectID; }
void Object::setName(const std::string& name) { m_sName = name; }
const std::string& Object::getName() const { return m_sName; }
void Object::setTag(int tag) { m_iTag = tag; }
int Object::getTag() const { return m_iTag; }
void Object::retain() { ++m_iReferenceCounts; }
void Object::release()
{
	--m_iReferenceCounts;
	if (m_iReferenceCounts == 0) { delete this; }
}
std::size_t Object::getReferenceCounts() const { return m_iReferenceCounts; }
void Object::autorelease()
{
	if (!m_bAutoreleaseEnable)
	{
		m_bAutoreleaseEnable = true;
		PoolManager::pushToDefaultPool(this);
	}
}
bool Object::isAutoreleaseEnable() const { return m_bAutoreleaseEnable; }
bool Object::insertVariableNumber(int varID, double varNum)
{
	auto ite = _numberVariableMap.find(varID);
	if (ite == _numberVariableMap.end())
	{
		_numberVariableMap.insert(std::make_pair(varID, varNum));
		return true;
	}
	return false;
}
bool Object::insertVariableString(int varID, const std::string& varNum)
{
	auto ite = _stringVariableMap.find(varID);
	if (ite == _stringVariableMap.end())
	{
		_stringVariableMap.insert(std::make_pair(varID, varNum));
		return true;
	}
	return false;
}

void Object::setVariableNumber(int varID, double varNum)
{
	_numberVariableMap[varID] = varNum;
}

void Object::setVariableString(int varID, const std::string& varNum)
{
	_stringVariableMap[varID] = varNum;
}

bool Object::removeVariableNumber(int varID)
{
	auto ite = _numberVariableMap.find(varID);
	if (ite != _numberVariableMap.end())
	{
		_numberVariableMap.erase(ite);
		return true;
	}
	return false;
}

bool Object::removeVariableString(int varID)
{
	auto ite = _stringVariableMap.find(varID);
	if (ite != _stringVariableMap.end())
	{
		_stringVariableMap.erase(ite);
		return true;
	}
	return false;
}

double Object::getVariableNumber(int varID) const
{
	auto ite = _numberVariableMap.find(varID);
	if (ite != _numberVariableMap.end())
	{
		return ite->second;
	}
	return CommonVariable::ERROR_NUMBER;
}

const std::string& Object::getVariableString(int varID) const
{
	auto ite = _stringVariableMap.find(varID);
	if (ite != _stringVariableMap.end())
	{
		return ite->second;
	}
	return _errorCodeStr;
}
