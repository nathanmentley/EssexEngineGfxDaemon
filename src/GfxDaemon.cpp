/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
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

using EssexEngine::Core::Models::IMessage;
using EssexEngine::Core::Models::IMessageResponse;
using EssexEngine::Core::Logging::LogDaemon;

using EssexEngine::Daemons::Gfx::GfxDaemon;
using EssexEngine::Daemons::Gfx::Entity;
using EssexEngine::Daemons::Gfx::ISprite;
using EssexEngine::Daemons::Gfx::IFont;
using EssexEngine::Daemons::Gfx::SpriteCacheKey;
using EssexEngine::Daemons::Gfx::FontCacheKey;
using EssexEngine::Daemons::Gfx::GfxDaemonMessage;
using EssexEngine::Daemons::Gfx::GfxDaemonMessageResponse;
using EssexEngine::Daemons::Gfx::Messages::MessageType;

using EssexEngine::Daemons::Window::IRenderContext;
using EssexEngine::Daemons::FileSystem::IFileBuffer;

GfxDaemon::GfxDaemon(WeakPointer<Context> _context):BaseProcessDaemon(_context),
    spriteCache(_context->GetDaemon<LogDaemon>()),
    fontCache(_context->GetDaemon<LogDaemon>()) {}

GfxDaemon::~GfxDaemon() {}

//non queued logic
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


//message generators
void GfxDaemon::SetupGfx() {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::SetupGfx,
                WeakPointer<IRenderContext>()
            )
        )
    );
}

void GfxDaemon::SetupRenderContext(WeakPointer<IRenderContext> target) {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::SetupRenderContext,
                target
            )
        )
    );
}

void GfxDaemon::StartRender(WeakPointer<IRenderContext> target) {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::StartRender,
                target
            )
        )
    );
}

void GfxDaemon::FinishRender(WeakPointer<IRenderContext> target) {
    UniquePointer<GfxDaemonMessageResponse> result = PushMessage<GfxDaemonMessageResponse>(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::FinishRender,
                target
            )
        )
    );
}

void GfxDaemon::RenderEntity(WeakPointer<IRenderContext> target, WeakPointer<Entity> entity) {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::RenderEntity,
                target,
                entity.Cast<void>()
            )
        )
    );
}

void GfxDaemon::RenderModel(WeakPointer<IRenderContext> target, WeakPointer<Model> model) {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::RenderModel,
                target,
                model.Cast<void>()
            )
        )
    );
}

void GfxDaemon::RenderString(WeakPointer<IRenderContext> target, WeakPointer<IFont> font, std::string data, int x, int y) {
    PushMessage(
        WeakPointer<IMessage>(
            new GfxDaemonMessage(
                MessageType::RenderString,
                target,
                font.Cast<void>(),
                Nullable<std::string>(data),
                Nullable<int>(x),
                Nullable<int>(y)
            )
        )
    );
}

//message parser
WeakPointer<IMessageResponse> GfxDaemon::ProcessMessage(WeakPointer<IMessage> message) {
    switch(message->GetType()) {
        case MessageType::SetupGfx:
            return _SetupGfx(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::SetupRenderContext:
            return _SetupRenderContext(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::StartRender:
            return _StartRender(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::FinishRender:
            return _FinishRender(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::RenderEntity:
            return _RenderEntity(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::RenderModel:
            return _RenderModel(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::RenderString:
            return _RenderString(message.Cast<GfxDaemonMessage>()).Cast<IMessageResponse>();
    }

    return WeakPointer<IMessageResponse>();
}

//message logic
WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_SetupGfx(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        GetDriver()->SetupGfx();
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_SetupRenderContext(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(message->GetTarget().HasValue()) {
            GetDriver()->SetupRenderContext(message->GetTarget());
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_StartRender(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(message->GetTarget().HasValue()) {
            GetDriver()->StartRender(message->GetTarget());
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_FinishRender(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(message->GetTarget().HasValue()) {
            GetDriver()->FinishRender(message->GetTarget());
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_RenderEntity(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(
            message->GetTarget().HasValue() &&
            message->GetData().HasValue()
        ) {
            GetDriver()->RenderEntity(
                message->GetTarget(),
                message->GetData().Cast<Entity>()
            );
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_RenderModel(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(
            message->GetTarget().HasValue() &&
            message->GetData().HasValue()
        ) {
            GetDriver()->RenderModel(
                message->GetTarget(),
                message->GetData().Cast<Model>()
            );
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}

WeakPointer<GfxDaemonMessageResponse> GfxDaemon::_RenderString(WeakPointer<GfxDaemonMessage> message) {
    if(HasDriver()) {
        if(
            message->GetTarget().HasValue() &&
            message->GetData().HasValue() &&
            message->GetMessage().HasValue() &&
            message->GetX().HasValue() &&
            message->GetY().HasValue()
        ) {
            GetDriver()->RenderString(
                message->GetTarget(),
                message->GetData().Cast<IFont>(),
                message->GetMessage().Get(),
                message->GetX().Get(),
                message->GetY().Get()
            );
        }
    }

    return WeakPointer<GfxDaemonMessageResponse>(
        new GfxDaemonMessageResponse()
    );
}
