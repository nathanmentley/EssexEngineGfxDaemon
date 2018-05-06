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
    class FontCacheKey {
        public:
            FontCacheKey(std::string _filename, int _fontSize) {
                filename = _filename;
                fontSize = _fontSize;
            }
            FontCacheKey() {
                filename = "";
                fontSize = -1;
            }

            bool operator==(const FontCacheKey &other) const {
                return filename == other.filename &&
                    fontSize == other.fontSize;
            }
            friend bool operator<(const FontCacheKey &l, const FontCacheKey &r) {
                if(l.filename < r.filename) {
                    return true;
                } else {
                    if(l.fontSize < r.fontSize) {
                        return true;
                    }

                    return false;
                }
            }
            friend bool operator>(const FontCacheKey &l, const FontCacheKey &r) {
                return !(r <= l);
            }
            friend bool operator<=(const FontCacheKey &l, const FontCacheKey &r) {
                return r == l || r < l;
            }
            friend bool operator>=(const FontCacheKey &l, const FontCacheKey &r) {
                return r == l || r > l;
            }

        private:
            std::string filename;
            int fontSize;
    };
};
