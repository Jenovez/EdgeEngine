// cpp文件

#include "PlatformManager.h"
#include "PlatformConfig.h"

#include <rapidjson/include/document.h>
#include <rapidjson/include/writer.h>
#include <utils/FileUtils.h>

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "win32/Win32PlatformFactory.h"
#elif TARGET_PLATFORM == PLATFORM_ANDROID
#elif TARGET_PLATFORM == PLATFORM_IOS
#elif TARGET_PLATFORM == PLATFORM_MAC
#elif TARGET_PLATFORM == PLATFORM_LINUX
#endif

#define WindowConfigPath "engine/platform.config"

USING_NS_EDGE;

PlatformManager::PlatformManager()
	: _factory(NULL)
	, _window(NULL)
	, _keyboard(NULL)
	, _mouse(NULL)
	, _resolutionSize()
	, m_sTitle("")
	, m_bShowConsole(false)
	, m_bFullScreen(false)
	, m_bShowCursor(false)
{}

PlatformManager::~PlatformManager()
{
}

PlatformManager* PlatformManager::getInstance()
{
	static PlatformManager _ins;
	return &_ins;
}

bool PlatformManager::loadConfig()
{
	if (!FileUtils::isFileExist(WindowConfigPath)) { return false; }
	rapidjson::Document doc;
	std::string jsonStr = FileUtils::readStringFromFile(WindowConfigPath);
	doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
	rapidjson::ParseErrorCode err = doc.GetParseError();
	if (doc.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone) { return false; }
	m_bFullScreen = doc["Full"].GetBool();
	_resolutionSize.setValue(doc["Width"].GetInt(), doc["Height"].GetInt());
	m_sTitle = doc["Title"].GetString();
	m_bShowConsole = doc["Console"].GetBool();
	m_bShowCursor = doc["Cursor"].GetBool();
	return true;
}

void PlatformManager::saveConfig()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember("Full", m_bFullScreen, doc.GetAllocator());
	doc.AddMember("Width", (int)_resolutionSize.width, doc.GetAllocator());
	doc.AddMember("Height", (int)_resolutionSize.height, doc.GetAllocator());
	doc.AddMember("Title", "EDGE", doc.GetAllocator());
	doc.AddMember("Console", m_bShowConsole, doc.GetAllocator());
	doc.AddMember("Cursor", m_bShowCursor, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string jsonStr = buffer.GetString();
	jsonStr.append("\n");
	bool ret = FileUtils::writeStringToFile(WindowConfigPath, jsonStr);
	assert(ret);
}

void PlatformManager::resetConfig()
{
	_resolutionSize.setValue(800, 600);
	m_sTitle = "EDGE";
	m_bShowConsole = false;
	m_bFullScreen = false;
	m_bShowCursor = true;
}

bool PlatformManager::startUp()
{
	SAFE_DELETE(_factory);
	SAFE_DELETE(_mouse);
	SAFE_DELETE(_keyboard);
	SAFE_DELETE(_window);

#if TARGET_PLATFORM == PLATFORM_WIN32
	_factory = new Win32PlatformFactory();
#elif TARGET_PLATFORM == PLATFORM_ANDROID
#elif TARGET_PLATFORM == PLATFORM_IOS
#elif TARGET_PLATFORM == PLATFORM_MAC
#elif TARGET_PLATFORM == PLATFORM_LINUX
#endif

	_window = _factory->createWindow();
	_keyboard = _factory->createKeyboard();
	_mouse = _factory->createMouse();

	if (!_window->initWindow(m_bFullScreen, m_sTitle, _resolutionSize)) { return false; }
	_window->showConsole(m_bShowConsole);
	_window->showCursor(m_bShowCursor);
	return true;
}

bool PlatformManager::shutDown()
{
	SAFE_DELETE(_factory);
	SAFE_DELETE(_mouse);
	SAFE_DELETE(_keyboard);
	SAFE_DELETE(_window);
	return true;
}

void PlatformManager::beginUpdate()
{}

void PlatformManager::update()
{
	_window->update(_keyboard, _mouse);
}

void PlatformManager::endUpdate()
{}

bool PlatformManager::isStop()
{
	if (!_window) { return true; }
	return (_window->getCurrentMessage() == EdgeMessage::QUIT);
}

IPlatformFactory* PlatformManager::getPlatformFactory() const { return _factory; }
IWindow* PlatformManager::getWindow() const { return _window; }
IKeyboard* PlatformManager::getKeyboard() const { return _keyboard; }
IMouse* PlatformManager::getMouse() const { return _mouse; }
