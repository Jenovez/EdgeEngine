/********************************************
名称:Application 应用程序
说明:
1.代理main函数的职责
********************************************/

#ifndef __APPLICATION_H_H__
#define __APPLICATION_H_H__

#include <base/CommonConfig.h>

typedef int(EdgeMainFunc(void));

NS_EDGE_BEGIN

class EDGE_DLL Application final
{
public:
	Application();
	~Application();

	int run(EdgeMainFunc func = NULL);

	void setIntervalTime(double second);
	double getIntervalTime() const;

private:
	void* operator new(std::size_t);
	void operator delete(void*);
	Application(const Application&);
	Application& operator=(const Application&);

private:
	ULong m_iIntervalTime;
};

NS_EDGE_END

#endif // __APPLICATION_H_H__