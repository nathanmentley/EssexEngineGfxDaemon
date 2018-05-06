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

using EssexEngine::CachedPointer;
using EssexEngine::UniquePointer;
using EssexEngine::WeakPointer;

using EssexEngine::Core::Logging::LogDaemon;

using EssexEngine::Daemons::Gfx::GfxDaemon;
using EssexEngine::Daemons::Gfx::Entity;
using EssexEngine::Daemons::Gfx::ISprite;
using EssexEngine::Daemons::Gfx::IFont;
using EssexEngine::Daemons::Gfx::SpriteCacheKey;
using EssexEngine::Daemons::Gfx::FontCacheKey;
using EssexEngine::Daemons::Window::IRenderContext;
using EssexEngine::Daemons::FileSystem::IFileBuffer;

GfxDaemon::GfxDaemon(WeakPointer<Context> _context):BaseDaemon(_context),
    spriteCache(_context->GetDaemon<LogDaemon>()),
    fontCache(_context->GetDaemon<LogDaemon>())
{
    primaryContext = WeakPointer<IRenderContext>();
}

GfxDaemon::~GfxDaemon() {}

void GfxDaemon::Setup(WeakPointer<IRenderContext> target)
{
    primaryContext = target;
    if(HasDriver()) {
        GetDriver()->Setup(target);
    }
}

void GfxDaemon::StartRender(WeakPointer<IRenderContext> target)
{
    if(HasDriver()) {
        GetDriver()->StartRender(target);
    }
}

void GfxDaemon::FinishRender(WeakPointer<IRenderContext> target)
{
    if(HasDriver()) {
        GetDriver()->FinishRender(target);
    }
}

void GfxDaemon::RenderEntity(WeakPointer<IRenderContext> target, WeakPointer<Entity> entity)
{
    if(HasDriver()) {
        GetDriver()->RenderEntity(target, entity);
    }
}

void GfxDaemon::RenderModel(WeakPointer<IRenderContext> target, WeakPointer<Model> model)
{
    if(HasDriver()) {
        GetDriver()->RenderModel(target, model);
    }
}

void GfxDaemon::RenderString(WeakPointer<IRenderContext> target, WeakPointer<IFont> font, std::string data, int x, int y) {
    if(HasDriver()) {
        GetDriver()->RenderString(target, font, data, x, y);
    }
}

CachedPointer<FontCacheKey, IFont> GfxDaemon::GetFont(WeakPointer<Window::IRenderContext> target, CachedPointer<std::string, FileSystem::IFileBuffer> fileContent, int fontSize) {
    FontCacheKey key = FontCacheKey(fileContent->GetFileName(), fontSize);

    if (!fontCache.HasKey(key)) {
        WeakPointer<IFont> font = GetDriver()->GetFont(target, std::move(fileContent), fontSize);
        fontCache.Cache(key, font);
    }

    return fontCache.Get(key);
}

CachedPointer<SpriteCacheKey, ISprite> GfxDaemon::GetSprite(WeakPointer<IRenderContext> target, CachedPointer<std::string, IFileBuffer> fileContent, int _x, int _y, int _width, int _height) {
    SpriteCacheKey key = SpriteCacheKey(fileContent->GetFileName(), _x, _y, _width, _height);

    if (!spriteCache.HasKey(key)) {
        WeakPointer<ISprite> sprite = GetDriver()->GetSprite(target, std::move(fileContent), _x, _y, _width, _height);
        spriteCache.Cache(key, sprite);
    }

    return spriteCache.Get(key);
}

UniquePointer<Entity> GfxDaemon::GetEntity(CachedPointer<SpriteCacheKey, ISprite> sprite) {
    return UniquePointer<Entity>(new Entity(std::move(sprite)));
}

WeakPointer<IRenderContext> GfxDaemon::GetPrimaryRenderContext() {
    return primaryContext;
}
