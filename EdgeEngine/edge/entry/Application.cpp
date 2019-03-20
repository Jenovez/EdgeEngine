// cpp文件

#include "Application.h"

#include <base/IManagerProtocol.h>
#include <platform/PlatformManager.h>
#include <renderer/RendererManager.h>
#include <audio/AudioManager.h>
#include <base/Director.h>

#include <rapidjson/include/document.h>
#include <utils/FileUtils.h>

#include <base/Input.h>

//#include <main.h>

#define ApplicationConfigPath "engine/application.config"

USING_NS_EDGE;

Application::Application()
: m_iIntervalTime(0)
{
}

Application::~Application()
{}

int Application::run(EdgeMainFunc edgeMainFunc)
{
	int returnCode = 0;

	std::vector<IManagerProtocol*> _managerList;

	PlatformManager* _platformMgr = PlatformManager::getInstance();
	RendererManager* _rendererMgr = RendererManager::getInstance();
	AudioManager* _audioMgr = AudioManager::getInstance();

	_managerList.push_back(_platformMgr);
	_managerList.push_back(_rendererMgr);
	_managerList.push_back(_audioMgr);

	Director* _director = Director::getInstance();
	_director->locatorApplication(this);
	_director->locatorPlatformManager(_platformMgr);
	_director->locatorRendererManager(_rendererMgr);
	_director->locatorAudioManager(_audioMgr);

	for (auto mgr : _managerList)
	{
		if (!mgr->loadConfig())
		{
			mgr->resetConfig();
			mgr->saveConfig();
		}
		if (!mgr->startUp())
		{
			returnCode = -1;
		}
	}

	Input::init();

	bool readRet = true;
	if (FileUtils::isFileExist(ApplicationConfigPath))
	{
		rapidjson::Document doc;
		std::string appConfigJson = FileUtils::readStringFromFile(ApplicationConfigPath);
		doc.Parse<0>(appConfigJson.c_str());
		rapidjson::ParseErrorCode jsonErr = doc.GetParseError();
		if (jsonErr != rapidjson::ParseErrorCode::kParseErrorNone)
		{
			readRet = false;
		}
		else
		{
			_director->runScene(Scene::create(doc["main_scene"].GetString()));
		}
	}
	else
	{
		readRet = false;
	}
	if (!readRet)
	{
		// write default config and create default scene
	}

	setIntervalTime(1 / 60.0);
	if (edgeMainFunc)
	{
		returnCode = edgeMainFunc();
	}

	if (returnCode == 0)
	{
		bool bStop = false;

		IWindow* window = _platformMgr->getWindow();

		ULong previousTime = window->getTickCount();
		ULong lagTime = 0;
		while (!bStop)
		{
			ULong currentTime = window->getTickCount();
			ULong elapsed = currentTime - previousTime;
			previousTime = currentTime;
			lagTime += elapsed;

			_platformMgr->beginUpdate();
			_platformMgr->update();
			_platformMgr->endUpdate();
			_director->onFastUpdate(elapsed);

			while (lagTime >= m_iIntervalTime)
			{
				double deltaTime = 0;
				if ((m_iIntervalTime == 0) || (lagTime / m_iIntervalTime > 10))
				{
					deltaTime = lagTime;
					lagTime = 0;
				}
				else
				{
					deltaTime = m_iIntervalTime / 1000.0;
					lagTime -= m_iIntervalTime;
				}

				_director->onUpdate(deltaTime);
				_director->onLateUpdate(deltaTime);

				_audioMgr->beginUpdate();
				_audioMgr->update();
				_audioMgr->endUpdate();

				if (lagTime == 0) { break; }
			}

			_rendererMgr->beginUpdate();
			_rendererMgr->update();
			_director->onRender(elapsed);
			_rendererMgr->endUpdate();

			if ((lagTime > 0) && (lagTime < m_iIntervalTime))
			{
				window->sleep(1);
			}

			for (auto mgr : _managerList)
			{
				bStop |= mgr->isStop();
			}
		};
	}
	
	_director->shutDown();

	while (!_managerList.empty())
	{
		if (!_managerList.back()->shutDown())
		{
			returnCode = -1;
		}
		_managerList.pop_back();
	}

	return returnCode;
}

void Application::setIntervalTime(double second)
{
	m_iIntervalTime = (ULong)(second * 1000.0);
	if (m_iIntervalTime < 0) { m_iIntervalTime = 0; }
}
double Application::getIntervalTime() const { return m_iIntervalTime / 1000.0; }
