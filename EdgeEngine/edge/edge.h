/********************************************
名称:
说明:
1.
********************************************/

#ifndef _EDGE_INCLUDE_H_H__
#define _EDGE_INCLUDE_H_H__

// audio folder
#include "audio/AudioCommon.h"
#include "audio/AudioConfig.h"
#include "audio/AudioDataCache.h"
#include "audio/AudioManager.h"
#include "audio/IAudio.h"
#include "audio/IAudioCircumstance.h"
#include "audio/IAudioDecoder.h"
#include "audio/IAudioFactory.h"

// base folder
#include "base/AutoReleasePool.h"
#include "base/CommonConfig.h"
#include "base/Director.h"
#include "base/EdgeTypes.h"
#include "base/IManagerProtocol.h"
#include "base/Object.h"
#include "base/PoolManager.h"
#include "base/Schedule.h"
#include "base/Input.h"

// components folder
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "components/ImageComponent.h"
#include "components/AudioComponent.h"

// entry folder
#include "entry/Application.h"

// objects folder
#include "objects/GameObject.h"
#include "objects/Scene.h"
#include "objects/ObjectFactory.h"

// platform folder
#include "platform/IKeyboard.h"
#include "platform/IMouse.h"
#include "platform/IWindow.h"
#include "platform/PlatformConfig.h"
#include "platform/PlatformMessage.h"
#include "platform/PlatformManager.h"
#include "platform/IPlatformFactory.h"

// renderer folder
#include "renderer/IGeometryGraphics.h"
#include "renderer/IRenderCircumstance.h"
#include "renderer/ITexture2D.h"
#include "renderer/ITexture2DRenderer.h"
#include "renderer/ITextureCache.h"
#include "renderer/RendererConfig.h"
#include "renderer/RendererManager.h"
#include "renderer/IRendererFactory.h"

// utils folder
#include "utils/FileUtils.h"

#endif // _EDGE_INCLUDE_H_H__