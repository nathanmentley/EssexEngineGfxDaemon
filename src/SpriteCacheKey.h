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

namespace EssexEngine::Daemons::Gfx {
    class SpriteCacheKey {
        public:
            SpriteCacheKey(std::string _filename, int _x, int _y, int _width, int _height) {
                filename = _filename;
                width = _width;
                height = _height;
                x = _x;
                y = _y;
            }
            SpriteCacheKey() {
                filename = "";
                width = 0;
                height = 0;
                x = 0;
                y = 0;
            }

            //TODO: Write correct logic for operators
            bool operator==(const SpriteCacheKey &other) const {
                return filename == other.filename &&
                    width == other.width &&
                    height == other.height &&
                    x == other.x &&
                    y == other.y;
            }
            friend bool operator<(const SpriteCacheKey &l, const SpriteCacheKey &r) {
                if(l.filename < r.filename) {
                    return true;
                } else if(l.filename > r.filename) {
                    return false;
                } else {
                    if(l.width < r.width) {
                        return true;
                    } else if (l.width > r.width) {
                        return false;
                    } else {
                        if(l.height < r.height) {
                            return true;
                        } else if (l.height > r.height) {
                            return false;
                        } else {
                            if(l.x < r.x) {
                                return true;
                            } else if (l.x > r.x) {
                                return false;
                            } else {
                                if(l.y < r.y) {
                                    return true;
                                } else {
                                    return false;
                                } 
                            } 
                        } 
                    } 
                }
            }
            friend bool operator>(const SpriteCacheKey &l, const SpriteCacheKey &r) {
                return !(r <= l);
            }
            friend bool operator<=(const SpriteCacheKey &l, const SpriteCacheKey &r) {
                return r == l || r < l;
            }
            friend bool operator>=(const SpriteCacheKey &l, const SpriteCacheKey &r) {
                return r == l || r > l;
            }

        private:
            std::string filename;
            int width;
            int height;
            int x;
            int y;
    };
};
