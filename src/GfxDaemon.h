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

#include <string>
#include <utility>

#include <EssexEngineCore/BaseDaemon.h>
#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/CachedPointer.h>
#include <EssexEngineCore/ResourceCache.h>

#include <EssexEngineGfxDaemon/IGfxDriver.h>
#include <EssexEngineGfxDaemon/SpriteCacheKey.h>

#include <EssexEngineWindowDaemon/IRenderContext.h>

namespace EssexEngine::Daemons::Gfx {
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
            
            void Setup(WeakPointer<Window::IRenderContext> target);
            void StartRender(WeakPointer<Window::IRenderContext> target);
            void FinishRender(WeakPointer<Window::IRenderContext> target);
            void RenderEntity(WeakPointer<Window::IRenderContext> target, WeakPointer<Entity> entity);
            void RenderModel(WeakPointer<Window::IRenderContext> target, WeakPointer<Model> model);
            void RenderString(WeakPointer<Window::IRenderContext> target, std::string data, int x, int y);
        
            CachedPointer<SpriteCacheKey, ISprite> GetSprite(CachedPointer<std::string, FileSystem::IFileBuffer> fileContent, int _x, int _y, int _width, int _height);
            UniquePointer<Entity> GetEntity(CachedPointer<SpriteCacheKey, ISprite> sprite);
            WeakPointer<Window::IRenderContext> GetPrimaryRenderContext();
        private:
            Core::Utils::ResourceCache<SpriteCacheKey, ISprite> spriteCache;
            WeakPointer<Window::IRenderContext> primaryContext;
    };
};
