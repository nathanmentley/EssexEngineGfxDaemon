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
#pragma once

#include <vector>

#include <EssexEngineGfxDaemon/Vector3.h>
#include <EssexEngineGfxDaemon/Mesh.h>
#include <EssexEngineGfxDaemon/Joint.h>

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
    class Model {
    public:
        Model() : position(0, 0, 0) {
            meshList = std::vector<Mesh>();
            jointList = std::vector<Joint>();
        }
    private:
        std::vector<Mesh> meshList;
        std::vector<Joint> jointList;
        Vector3<float> position;
    };
}}};
