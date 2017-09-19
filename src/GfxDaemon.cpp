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

#include <EssexEngineGfxDaemon/GfxDaemon.h>

EssexEngine::Daemons::Gfx::GfxDaemon::GfxDaemon(WeakPointer<Context> _context):BaseDaemon(_context) {}

EssexEngine::Daemons::Gfx::GfxDaemon::~GfxDaemon() {}

extern "C" {
    void daemon_init(EssexEngine::Context* context) {
        context->RegisterDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>(
            new EssexEngine::Daemons::Gfx::GfxDaemon(context)
        );
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::Setup()
{
    if(HasDriver()) {
        GetDriver()->Setup();
    }
}

int EssexEngine::Daemons::Gfx::GfxDaemon::GetScreenWidth()
{
    return GetDriver()->GetScreenWidth();
}

int EssexEngine::Daemons::Gfx::GfxDaemon::GetScreenHeight()
{
    return GetDriver()->GetScreenHeight();
}

void EssexEngine::Daemons::Gfx::GfxDaemon::StartRender()
{
    if(HasDriver()) {
        GetDriver()->StartRender();
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::FinishRender()
{
    if(HasDriver()) {
        GetDriver()->FinishRender();
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderEntity(WeakPointer<Entity> entity)
{
    if(HasDriver()) {
        GetDriver()->RenderEntity(entity);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderModel(WeakPointer<Model> model)
{
    if(HasDriver()) {
        GetDriver()->RenderModel(model);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderString(std::string data, int x, int y) {
    if(HasDriver()) {
        GetDriver()->RenderString(data, x, y);
    }
}

EssexEngine::SharedPointer<EssexEngine::Daemons::Gfx::ISprite> EssexEngine::Daemons::Gfx::GfxDaemon::GetSprite(WeakPointer<FileSystem::IFileBuffer> fileContent, int _x, int _y, int _width, int _height) {
    return GetDriver()->GetSprite(fileContent, _x, _y, _width, _height);
}

EssexEngine::SharedPointer<EssexEngine::Daemons::Gfx::Entity> EssexEngine::Daemons::Gfx::GfxDaemon::GetEntity(WeakPointer<ISprite> sprite) {
    return SharedPointer<Entity>(new Entity(sprite));
}
