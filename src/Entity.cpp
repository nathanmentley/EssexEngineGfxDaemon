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

#include <EssexEngineGfxDaemon/Entity.h>

EssexEngine::Daemons::Gfx::Entity::Entity(CachedPointer<Gfx::SpriteCacheKey, Gfx::ISprite> _sprite) : sprite(std::move(_sprite))
{
    x = 0;
    y = 0;
    scaleX = 1;
    scaleY = 1;
}

EssexEngine::Daemons::Gfx::Entity::~Entity()
{
}

EssexEngine::WeakPointer<EssexEngine::Daemons::Gfx::ISprite> EssexEngine::Daemons::Gfx::Entity::GetSprite() {
    return sprite.ToWeakPointer();
}

int EssexEngine::Daemons::Gfx::Entity::GetX()
{
    return x;
}

int EssexEngine::Daemons::Gfx::Entity::GetY()
{
    return y;
}

float EssexEngine::Daemons::Gfx::Entity::GetScaleX()
{
    return scaleX;
}

float EssexEngine::Daemons::Gfx::Entity::GetScaleY()
{
    return scaleY;
}

void EssexEngine::Daemons::Gfx::Entity::SetPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

void EssexEngine::Daemons::Gfx::Entity::SetScale(float _scaleX, float _scaleY)
{
    scaleX = _scaleX;
    scaleY = _scaleY;
}
