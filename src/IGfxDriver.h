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
#include <memory>

#include <EssexEngineCore/IDriver.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/CachedPointer.h>

#include <EssexEngineGfxDaemon/Entity.h>
#include <EssexEngineGfxDaemon/Model.h>

#include <EssexEngineFileSystemDaemon/IFileBuffer.h>

#include <EssexEngineWindowDaemon/IRenderContext.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
    class IGfxDriver: public Core::IDriver
    {
        public:
            virtual void Setup(WeakPointer<Window::IRenderContext> target) = 0;
        
            virtual void StartRender(WeakPointer<Window::IRenderContext> target) = 0;
            virtual void FinishRender(WeakPointer<Window::IRenderContext> target) = 0;
            
            virtual void RenderEntity(WeakPointer<Window::IRenderContext> target, WeakPointer<Entity> entity) = 0;
            virtual void RenderModel(WeakPointer<Window::IRenderContext> target, WeakPointer<Model> model) = 0;
            virtual void RenderString(WeakPointer<Window::IRenderContext> target, std::string data, int x, int y) = 0;
        
            virtual WeakPointer<ISprite> GetSprite(WeakPointer<Daemons::Window::IRenderContext> target, CachedPointer<std::string, FileSystem::IFileBuffer> fileContent, int _x, int _y, int _width, int _height) = 0;
        private:
    };
}}};
