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

#include "item_manager.hpp"
#include "game.hpp"

extern game_class game;

//----------------------------------------------------------------------------------------------------------------

item_class::item_class(void)
{
    item_class::name               = "";
    item_class::active             = false;
};

item_class::~item_class(void)
{
};

//----------------------------------------------------------------------------------------------------------------

item_manager_class::item_manager_class(void)
{
};

item_manager_class::~item_manager_class(void)
{
};

void item_manager_class::reset_item(int item_number)
{
    item_manager_class::item[item_number].type                   = NULL_ITEM;
    item_manager_class::item[item_number].name                   = "";
    item_manager_class::item[item_number].quantity               = 1;
    item_manager_class::item[item_number].quantity_max           = 1;
    item_manager_class::item[item_number].active                 = false;
    item_manager_class::item[item_number].socketable             = false;
    item_manager_class::item[item_number].number_of_item_effects = 0;
    item_manager_class::item[item_number].number_of_item_sockets = 0;
    for (int item_effect_count = 0; item_effect_count < MAX_ITEM_EFFECTS; item_effect_count++)
    {
        item_manager_class::item[item_number].effect[item_effect_count].type = NULL_ITEM;
    }
    for (int item_socket_count = 0; item_socket_count < MAX_ITEM_SOCKETS; item_socket_count++)
    {
        item_manager_class::item[item_number].socket[item_socket_count].type = NULL_ITEM;
    }
};

int item_manager_class::get_new_ID(void)
{
    for (int item_count = 0; item_count < MAX_ITEMS; item_count++)
    {
        if (!item_manager_class::item[item_count].active) return (item_count);
    }
    return (-1);
};

int item_manager_class::get_item_ID(int temp_item_type)
{
    for (int item_count = 0; item_count < MAX_ITEMS; item_count++)
    {
        if (item_manager_class::item[item_count].ID == temp_item_type) return (item_count);
    }
    return (-1);
};

//----------------------------------------------------------------------------------------------------------------

void  init_items(void) // Initialize hard-coded default items, such as health potions etc...
{
    //------------------------------------------------------------------------------------------------------------
    int item_number = -1;
    //------------------------- Potions --------------------------------------------------------------------------
    item_number = game.item_manager.get_new_ID();
    if (item_number > -1) // Health potion
    {
        game.item_manager.reset_item(item_number);
        game.item_manager.item[item_number].active                 = true;
        game.item_manager.item[item_number].type                   = HEALTH_POTION;
        game.item_manager.item[item_number].ID                     = item_number;
        game.item_manager.item[item_number].quantity               = 1;
        game.item_manager.item[item_number].quantity_max           = 1;
        game.item_manager.item[item_number].active                 = false;
        game.item_manager.item[item_number].socketable             = false;
        game.item_manager.item[item_number].number_of_item_sockets = 1;
        game.item_manager.item[item_number].number_of_item_effects = 1;
        game.item_manager.item[item_number].effect[0].type         = EFFECT_MOD_HEALTH;
        game.item_manager.item[item_number].effect[0].value        = 5.0f;
        game.item_manager.item[item_number].image.path             = "data/textures/UI/icons/potions/potion_23.png";
        game.item_manager.item[item_number].image.load_image(game.item_manager.item[item_number].image.path);
    }
    //------------------------------------------------------------------------------------------------------------
};

