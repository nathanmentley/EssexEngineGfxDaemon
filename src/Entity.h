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

#include <EssexEngineCore/CachedPointer.h>
#include <EssexEngineGfxDaemon/ISprite.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
	class Entity
	{
		public:
			Entity(CachedPointer<ISprite> _sprite);
			~Entity();
        
            void SetPosition(int _x, int _y);
            void SetScale(float _scaleX, float _scaleY);
            int GetX();
            int GetY();
            float GetScaleX();
            float GetScaleY();
        
            WeakPointer<ISprite> GetSprite();
		protected:
		private:
            CachedPointer<ISprite> sprite;
			int x;
			int y;
            float scaleX;
            float scaleY;
	};
}}};
