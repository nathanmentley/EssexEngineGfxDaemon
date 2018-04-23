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

EssexEngine::Daemons::Gfx::GfxDaemon::GfxDaemon(WeakPointer<Context> _context):BaseDaemon(_context),
    spriteCache(_context->GetDaemon<Core::Logging::LogDaemon>()) {
    primaryContext = WeakPointer<Window::IRenderContext>();
}

EssexEngine::Daemons::Gfx::GfxDaemon::~GfxDaemon() {}

extern "C" {
    void daemon_init(EssexEngine::Context* context) {
        context->RegisterDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>(
            new EssexEngine::Daemons::Gfx::GfxDaemon(context)
        );
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::Setup(WeakPointer<Window::IRenderContext> target)
{
    primaryContext = target;
    if(HasDriver()) {
        GetDriver()->Setup(target);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::StartRender(WeakPointer<Window::IRenderContext> target)
{
    if(HasDriver()) {
        GetDriver()->StartRender(target);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::FinishRender(WeakPointer<Window::IRenderContext> target)
{
    if(HasDriver()) {
        GetDriver()->FinishRender(target);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderEntity(WeakPointer<Window::IRenderContext> target, WeakPointer<Entity> entity)
{
    if(HasDriver()) {
        GetDriver()->RenderEntity(target, entity);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderModel(WeakPointer<Window::IRenderContext> target, WeakPointer<Model> model)
{
    if(HasDriver()) {
        GetDriver()->RenderModel(target, model);
    }
}

void EssexEngine::Daemons::Gfx::GfxDaemon::RenderString(WeakPointer<Window::IRenderContext> target, std::string data, int x, int y) {
    if(HasDriver()) {
        GetDriver()->RenderString(target, data, x, y);
    }
}

EssexEngine::CachedPointer<EssexEngine::Daemons::Gfx::SpriteCacheKey, EssexEngine::Daemons::Gfx::ISprite> EssexEngine::Daemons::Gfx::GfxDaemon::GetSprite(CachedPointer<std::string, FileSystem::IFileBuffer> fileContent, int _x, int _y, int _width, int _height) {
    SpriteCacheKey key = SpriteCacheKey(fileContent->GetFileName(), _x, _y, _width, _height);

    if (!spriteCache.HasKey(key)) {
        WeakPointer<ISprite> sprite = GetDriver()->GetSprite(std::move(fileContent), _x, _y, _width, _height);
        spriteCache.Cache(key, sprite);
    }

    return spriteCache.Get(key);
}

EssexEngine::UniquePointer<EssexEngine::Daemons::Gfx::Entity> EssexEngine::Daemons::Gfx::GfxDaemon::GetEntity(CachedPointer<SpriteCacheKey, ISprite> sprite) {
    return UniquePointer<Entity>(new Entity(std::move(sprite)));
}

EssexEngine::WeakPointer<EssexEngine::Daemons::Window::IRenderContext> EssexEngine::Daemons::Gfx::GfxDaemon::GetPrimaryRenderContext() {
    return primaryContext;
}
