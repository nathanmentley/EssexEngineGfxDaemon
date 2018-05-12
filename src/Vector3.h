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

namespace EssexEngine{
namespace Daemons{
namespace Gfx{
	template <class vType> class Vector3
	{
        public:
            Vector3(vType _x, vType _y, vType _z) {
                x = _x;
                y = _y;
                z = _z;
            }
            vType GetX() { return x; }
            vType GetY() { return y; }
            vType GetZ() { return z; }
		protected:
        private:
            vType x;
            vType y;
            vType z;
	};
}}};
