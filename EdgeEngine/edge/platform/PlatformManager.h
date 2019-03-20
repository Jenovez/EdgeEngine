/********************************************
名称:
说明:
1.
********************************************/

#ifndef __PLATFORM_MANAGER_H_H__
#define __PLATFORM_MANAGER_H_H__

#include <base/IManagerProtocol.h>

#include "IWindow.h"
#include "IKeyboard.h"
#include "IMouse.h"
#include "IPlatformFactory.h"

NS_EDGE_BEGIN

class EDGE_DLL PlatformManager final : public IManagerProtocol
{
public:
	static PlatformManager* getInstance();

public:// implements
	bool loadConfig();
	void saveConfig();
	void resetConfig();

	bool startUp();
	bool shutDown();

	void beginUpdate();
	void update();
	void endUpdate();

	bool isStop();

public:
	IPlatformFactory* getPlatformFactory() const;
	IWindow* getWindow() const;
	IKeyboard* getKeyboard() const;
	IMouse* getMouse() const;

private:
	PlatformManager();
	~PlatformManager();
	PlatformManager(const PlatformManager&);
	PlatformManager& operator=(const PlatformManager&);

private:
	IPlatformFactory* _factory;
	IWindow* _window;
	IKeyboard* _keyboard;
	IMouse* _mouse;

private: // config
	Size _resolutionSize; // 分辨率
	std::string m_sTitle; // 标题
	bool m_bShowConsole; // 是否显示控制台
	bool m_bFullScreen; // 是否全屏
	bool m_bShowCursor; // 是否显示光标
};

NS_EDGE_END

#endif // __PLATFORM_MANAGER_H_H__