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
#include <vector>

#include <EssexEngineGfxDaemon/ISprite.h>
#include <EssexEngineGfxDaemon/Vertex.h>
#include <EssexEngineGfxDaemon/Weight.h>
#include <EssexEngineGfxDaemon/Vector3.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
	class Mesh
	{
        public:
            Mesh() {
                shader = "";
                vertexes = std::vector<Vertex>();
                weights = std::vector<Weight>();
                triangles = std::vector<Vector3<int>>();
                texture = 0;
            }
		protected:
        private:
            std::string shader;
            std::vector<Vertex> vertexes;
            std::vector<Weight> weights;
            std::vector<Vector3<int>> triangles;
            ISprite* texture;
	};
}}};