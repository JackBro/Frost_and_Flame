/**
 * Copyright (C) 2011-2013 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../core/pathfinding.hpp"
#include "../core/texture_manager.hpp"

#define MAX_PLAYERS 4

#define MOVE_TO_TILE_NONE          0
#define MOVE_TO_TILE_MOVE          1
#define MOVE_TO_TILE_ATTACK        2
#define MOVE_TO_TILE_PICKUP_ITEM   3
#define MOVE_TO_TILE_USE_OBJECT    4

const int MAX_LEVELS = 100+1;

class level_class
{
    public:
        level_class(void);
       ~level_class(void);
        float                multiplier;
        int                  base;
        int                  current;
        unsigned long long   current_experience;
        unsigned long long   experience[MAX_LEVELS];
        void                 init(void);
        void                 process(void);
};

class stat_class
{
    public:
        stat_class(void);
       ~stat_class(void);
        float             width;
        float             height;
        float             pos_x;
        float             pos_y;
        float             pos_z;
        float             current;
        float             maximum;
        float             regeneration;
        void              process(void);
        void              draw(void);
};

class player_class
{
    public:
        player_class(void);
       ~player_class(void);
        texture_type      *portrait;
        std::string        name;
        level_class        level;
        unsigned long long gold;
        int                offence;
        int                defense;
        int                intellect;
        float              armor;
        float              critical_chance;
        float              walk_speed;
        float              light_radius;
        float              damage_physical_maximum;
        float              damage_physical_minimum;
        float              damage_frost;
        float              damage_flame;
        float              damage_lightning;
        float              resistance_frost;
        float              resistance_flame;
        float              resistance_lightning;
        int                allocatable_points;
        bool               auto_allocate;
        float              pos_x;
        float              pos_y;
        float              pos_z;
        int                destination_tile;
        bool               destination_set;
        bool               path_set;
        int                movement_type;
        stat_class         mana;
        stat_class         health;
        void               process(void);
        void               render(void);
        void               path_calculate(void);
        void               player_move(void);
        void               player_attack(void);
        void               player_pickup_item(void);
        void               player_use_object(void);
};

#endif // PLAYER_H
