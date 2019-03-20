/********************************************
名称:Object 对象
说明:
1.最基类
********************************************/

#ifndef __OBJECT_H_H__
#define __OBJECT_H_H__

#include "CommonConfig.h"
#include "EdgeTypes.h"

NS_EDGE_BEGIN

class EDGE_DLL Object
{
public:
	virtual ~Object();

public: // 一般属性
	/**
	* 设置ObjectID
	*/
	virtual void setObjectID(int id) final;

	/**
	* 获得ObjectID
	*/
	virtual int getObjectID() const final;

	/**
	* 设置name
	*/
	virtual void setName(const std::string& name) final;

	/**
	* 获得name
	*/
	virtual const std::string& getName() const final;

	/**
	* 设置tag
	*/
	virtual void setTag(int tag) final;

	/**
	* 获得tag
	*/
	virtual int getTag() const final;

public: // 引用计数管理内存
	/**
	* 引用计数+1
	*/
	virtual void retain() final;
	/**
	* 引用计数-1
	* 如果没有autorelease则直接释放内存delete this;
	*/
	virtual void release() final;
	/**
	* 获得当前引用计数
	*/
	virtual std::size_t getReferenceCounts() const final;
	/**
	* 自动管理内存
	*/
	virtual void autorelease() final;
	/**
	* 是否自动管理内存,即是否已经调用过autorelease
	*/
	virtual bool isAutoreleaseEnable() const final;

public: // 变量管理
	/**
	* 插入一个double数值变量
	* 参数1:变量唯一ID
	* 参数2:double数值
	* 返回值:是否插入成功
	*/
	virtual bool insertVariableNumber(int varID, double varNum) final;
	/**
	* 插入一个string变量
	* 参数1:变量唯一ID
	* 参数2:string数值
	* 返回值:是否插入成功
	*/
	virtual bool insertVariableString(int varID, const std::string& varNum) final;

	/**
	* 删除一个double数值变量
	* 参数1:变量的ID
	* 返回值:是否删除成功
	*/
	virtual bool removeVariableNumber(int varID) final;
	/**
	* 删除一个string变量
	* 参数1:变量的ID
	* 返回值:是否删除成功
	*/
	virtual bool removeVariableString(int varID) final;

	/**
	* 设置一个数值变量
	* 参数1:变量ID
	* 参数2:double数值
	* 如果id不存在则调用insertVariableNumber插入
	*/
	virtual void setVariableNumber(int varID, double varNum) final;
	/**
	* 设置一个String变量
	* 参数1:变量ID
	* 参数2:string数值
	* 如果id不存在则调用insertVariableString插入
	*/
	virtual void setVariableString(int varID, const std::string& varNum) final;

	/**
	* 获得double数值变量
	* 参数:变量唯一ID
	* 返回值:double数值,如果不存在返回CommonVariable::ERROR_NUMBER
	*/
	virtual double getVariableNumber(int varID) const final;
	/**
	* 获得string变量
	* 参数:变量唯一ID
	* 返回值:int数值,如果不存在返回CommonVariable::ERROR_STRING;
	*/
	virtual const std::string& getVariableString(int varID) const final;

protected:
	Object();

private:
	Object(const Object&);
	Object& operator=(const Object&);

private:
	int m_iObjectID; // 对象ID
	std::string m_sName; // name
	int m_iTag; // tag

private:
	std::size_t m_iReferenceCounts; // 引用计数,用于内存管理

private:
	std::map<int, double> _numberVariableMap; // 存放数值变量的map
	std::map<int, std::string> _stringVariableMap; // 存放字符串变量的map
	std::string _errorCodeStr; // 错误字符串

private:
	bool m_bAutoreleaseEnable; // 是否自动管理内存
};

NS_EDGE_END

#endif // __OBJECT_H_H__