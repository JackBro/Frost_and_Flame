/**
 * Copyright (C) Paul Wortmann, PhysHex Games, www.physhexgames.com
 * This file is part of "Frost And Flame"
 *
 * "Frost And Flame" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 only.
 *
 * "Frost And Flame" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "Frost And Flame" If not, see <http://www.gnu.org/licenses/>.
 *
 * @author  Paul Wortmann
 * @email   physhex@gmail.com
 * @website www.physhexgames.com
 * @license GPL V2
 * @date 2011-11-11
 */

#ifndef RE_GRAPHICS_HPP
#define RE_GRAPHICS_HPP

#include <cstdlib>
#include <cstdint>
#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GL/gl.h>
#include "../wrappers/re_sdl_graphics.hpp"

namespace RoboEngine
{

    class re_cGraphicsEngine
    {
        public:
            re_cGraphicsEngine(void) {}
            virtual ~re_cGraphicsEngine(void) {}
            re_cGraphicsEngine(const re_cGraphicsEngine&) = default;
            re_cGraphicsEngine& operator=(const re_cGraphicsEngine& rhs) {if (this == &rhs) return *this; return *this;}
            void initialize(void);
            void deinitialize(void);
            void process(void);
        private:
            RE_Window *m_window = nullptr;
            RE_GLContext m_glcontext = {};
    };

}
#endif // RE_GRAPHICS_HPP