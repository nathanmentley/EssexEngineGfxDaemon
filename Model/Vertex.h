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

#include <EssexEngineGfxDaemon/Vector2.h>
#include <EssexEngineGfxDaemon/Vector3.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
	class Vertex
	{
        public:
            Vertex() :
                position(0, 0, 0), normal(0, 0, 0), texture(0, 0)
            {
                startWeight = 0;
                weightCount = 0;
            }
		protected:
        private:
            Vector3<float> position;
            Vector3<float> normal;
            Vector2<float> texture;
            int startWeight;
            int weightCount;
	};
}}};