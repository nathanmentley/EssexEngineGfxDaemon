/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */
#pragma once

#include <utility>

#include <EssexEngineCore/BaseDaemon.h>
#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/CachedPointer.h>
#include <EssexEngineCore/ResourceCache.h>
#include <EssexEngineGfxDaemon/IGfxDriver.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
	class GfxDaemon:public BaseDaemon<IGfxDriver>
	{
		public:
			GfxDaemon(WeakPointer<Context> _context);
			~GfxDaemon();
			
			void Init() {
				if(GetContext()->HasDaemon<Core::Logging::LogDaemon>()) {
					GetContext()->GetDaemon<Core::Logging::LogDaemon>()->LogLine(
						"Loading Daemon [%s] [%s]",
						GetDaemonName().c_str(),
						GetDaemonVersion().c_str()
					);
				}
			}
			std::string GetDaemonName() { return "Gfx"; }
			std::string GetDaemonVersion() { return ESSEX_ENGINE_VERSION; }
			
            void Setup();
            int GetScreenWidth();
            int GetScreenHeight();
            void StartRender();
            void FinishRender();
            void RenderEntity(WeakPointer<Entity> entity);
            void RenderModel(WeakPointer<Model> model);
            void RenderString(std::string data, int x, int y);
		
			CachedPointer<ISprite> GetSprite(CachedPointer<FileSystem::IFileBuffer> fileContent, int _x, int _y, int _width, int _height);
			UniquePointer<Entity> GetEntity(CachedPointer<ISprite> sprite);
		private:
			Core::Utils::ResourceCache<ISprite> spriteCache;
	};
}}};
