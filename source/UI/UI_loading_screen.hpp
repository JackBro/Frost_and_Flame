/**
 * Copyright (C) 2011-2014 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
 * This file is part of "Frost And Flame"
 *
 * "Frost And Flame" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
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
 * @website www.physhexgames.co.nr
 * @license GPL V3
 * @date 2011-11-11
 */

#ifndef UI_LOADING_SCREEN_H
#define UI_LOADING_SCREEN_H

#include <string>
#include "../core/texture_manager.hpp"

class UI_loading_screen_class
{
    protected:
    private:
        texture_type* texture;
    public:
        UI_loading_screen_class () : texture(NULL) {};
        ~UI_loading_screen_class () {if (texture) delete texture;};
        void display(std::string file_name);
};

#endif // UI_LOADING_SCREEN_H

