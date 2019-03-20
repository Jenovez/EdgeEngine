/********************************************
名称:
说明:
1.
********************************************/

#ifndef __I_MANAGER_PROTOCOL_H_H__
#define __I_MANAGER_PROTOCOL_H_H__

#include "CommonConfig.h"
#include "EdgeTypes.h"

NS_EDGE_BEGIN

class EDGE_DLL IManagerProtocol
{
public:
	virtual ~IManagerProtocol() {}

	virtual bool loadConfig() = 0;
	virtual void saveConfig() = 0;
	virtual void resetConfig() = 0;

	virtual bool startUp() = 0;
	virtual bool shutDown() = 0;

	virtual void beginUpdate() = 0;
	virtual void update() = 0;
	virtual void endUpdate() = 0;

	virtual bool isStop() = 0;

protected:
	IManagerProtocol() {}
private:
	IManagerProtocol(const IManagerProtocol&);
	IManagerProtocol& operator=(const IManagerProtocol&);
};

NS_EDGE_END

#endif // __I_MANAGER_PROTOCOL_H_H__