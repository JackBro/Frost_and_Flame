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

#include "core/map_2D.hpp"
#include "game.hpp"

game_class        game;

game_class::game_class(void)
{
    game_class::event = 0;
    game_class::state = STATE_MENU;
};

void game_class::init(void)
{
    game_class::debug = false;
    glDisable(GL_DEPTH_TEST);
    //--- initial state of the background ---
    game.core.background.set_data ( 1, 1, 0, 0.0f, 0.0f, 0.0000f, 0.00000f, "data/textures/UI/backgrounds/background_01.png");
    game.core.background.set_data ( 2, 1, 0, 0.0f, 0.0f, 0.0000f, 0.00000f, "data/textures/UI/backgrounds/background_01.png");
    game.core.background.set_data ( 3, 1, 0, 0.0f, 0.0f, 0.0010f, 0.00065f, "data/textures/UI/backgrounds/background_03.png");
    game.core.background.set_data ( 4, 1, 0, 4.0f, 0.0f, 0.0010f, 0.00065f, "data/textures/UI/backgrounds/background_03.png");
    game.core.background.set_data ( 5, 1, 0, 0.0f, 0.0f, 0.0040f, 0.00075f, "data/textures/UI/backgrounds/background_03.png");
    game.core.background.set_data ( 6, 1, 0, 4.0f, 0.0f, 0.0040f, 0.00075f, "data/textures/UI/backgrounds/background_03.png");
    game.core.background.set_movement_type(FRONT_SCROLL);
    //--- other ---

    //game.model_3D.tree_palm.save("test_palm.obj");
    game.global_ambient.intensity_R = 8.0f;
    game.global_ambient.intensity_G = 8.0f;
    game.global_ambient.intensity_B = 8.0f;
    game.global_ambient.intensity_A = 8.0f;
    game.world_ambient.intensity_R  = 2.0f;
    game.world_ambient.intensity_G  = 2.0f;
    game.world_ambient.intensity_B  = 2.0f;
    game.world_ambient.intensity_A  = 2.0f;
    game.world_ambient.increase     = true;
    game.world_ambient.speed        = 0.0125f;
    game.zoom.current                             = TILE_SCALE_DEFAULT;
    game.zoom.min                                 = 80.0f;
    game.zoom.max                                 = 400.0f;
    game.zoom.speed                               = 200.5f;

    game.core.game_paused                         = false;
    game.core.game_active                         = false;
    game.core.game_resume                         = false;
    game.core.quest_log_active                    = false;
    game.core.character_active                    = false;
    game.core.skillbook_active                    = false;
    game.core.inventory_active                    = false;
    game.core.npcvendor_active                    = false;

    game.player.name                              =  "Kanchi";
    game.player.level.current                     =  0;
    game.player.level.base                        =  2;
    game.player.level.multiplier                  =  1.52f;
    game.player.level.init();
    game.player.level.current_experience          =  2; // 0 for norm
    game.player.health.current                    =  000.0f;
    game.player.health.maximum                    =  100.0f;
    game.player.health.regeneration               =  000.015f;
    game.player.mana.current                      =  000.0f;
    game.player.mana.maximum                      =  100.0f;
    game.player.mana.regeneration                 =  000.025f;

    game.player.destination_tile                  =  0;
    game.player.destination_set                   =  false;
    game.player.path_set                          =  false;
    game.player.movement_type                     =  MOVE_TO_TILE_NONE;

    //--- other ---
    game.core.music_next_track = true;
    init_spells();
    init_items();

    //game.map_2D.load("data/maps/town.tmx");
    game.map_2D.random_map(100,100,CAVE,CAVE);

    //zoom out for testing
    game.zoom.current = game.zoom.max;
    game.map_2D.calculate_tile_positions(DEFAULT_FRAME_WIDTH/game.zoom.current/2.0f,DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);

    // Add default items to inventory
    int inventory_ID = game.window_manager.window_get_number(INVENTORY_UID);
    int item_ID = 0;
    item_ID = game.item_manager.get_item_ID(HEALTH_POTION); // Health Potion
    game.window_manager.window[inventory_ID].element[1].value    = item_ID;
    game.window_manager.window[inventory_ID].element[1].quantity = 1;
    game.window_manager.window[inventory_ID].element[1].texture.normal.image.load_image(game.item_manager.item[item_ID].image.path);
    item_ID = game.item_manager.get_item_ID(MANA_POTION); // Mana Potion
    game.window_manager.window[inventory_ID].element[2].value = item_ID;
    game.window_manager.window[inventory_ID].element[2].quantity = 2;
    game.window_manager.window[inventory_ID].element[2].texture.normal.image.load_image(game.item_manager.item[item_ID].image.path);
};

void game_class::reload_rextures(void)
{

};

void game_class::process(void)
{
    game.player.process();
    game.npc.process();
    game.map_2D.process();
    //game.resource.map_3D.town.process();
    game.core.game_resume = true;
    if (game.core.music_next_track)
    {
        game.core.music_next_track = false;
        //if (game.core.music_track ==  0) game.resource.music.menu_00.play();
    }
    if (game.core.io.mouse_wheel != 0)
    {
        if (game.core.io.mouse_wheel < 0)
        {
            while (game.core.io.mouse_wheel < 0)
            {
                game.core.io.mouse_wheel++;
                game.zoom.current += game.zoom.speed;
            }
            if (game.zoom.current > game.zoom.max) game.zoom.current = game.zoom.max;
            else
            {
                //game.resource.map_2D.tile[0].pos_y -= (DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);
                //game.resource.map_2D.calculate_tile_positions(DEFAULT_FRAME_WIDTH/game.zoom.current/2.0f,DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);
            }
        }
        if (game.core.io.mouse_wheel > 0)
        {
            while (game.core.io.mouse_wheel > 0)
            {
                game.core.io.mouse_wheel--;
                game.zoom.current -= game.zoom.speed;
            }
            if (game.zoom.current < game.zoom.min) game.zoom.current = game.zoom.min;
            else
            {
                //game.resource.map_2D.tile[0].pos_y += (DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);
                //game.resource.map_2D.calculate_tile_positions(DEFAULT_FRAME_WIDTH/game.zoom.current/2.0f,DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);
            }
        }
    }
    if (game.core.io.keyboard_ready)
    {
        if (game.core.io.key_escape) // Main menu
        {
            if (!game.core.game_menu_active)
            {
                game.window_manager.window_enable(MENU_MAIN_UID);
                game.core.game_menu_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(MENU_MAIN_UID);
                game.core.game_menu_active                   = false;
            }
            game.core.io.key_escape                = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_c) // Character menu
        {
            if (!game.core.character_active)
            {
                game.window_manager.window_enable(CHARACTER_UID);
                game.core.character_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(CHARACTER_UID);
                game.core.character_active                   = false;
            }
            game.core.io.key_c                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_e) // Equipment menu
        {
            if (!game.core.equipment_active)
            {
                game.window_manager.window_enable(EQUIPMENT_UID);
                game.core.equipment_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(EQUIPMENT_UID);
                game.core.equipment_active                   = false;
            }
            game.core.io.key_e                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_q) // Quest log menu
        {
            if (!game.core.quest_log_active)
            {
                game.window_manager.window_enable(QUEST_LOG_UID);
                game.core.quest_log_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(QUEST_LOG_UID);
                game.core.quest_log_active                   = false;
            }
            game.core.io.key_q                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_i) // Inventory menu
        {
            if (!game.core.inventory_active)
            {
                game.window_manager.window_enable(INVENTORY_UID);
                game.core.inventory_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(INVENTORY_UID);
                game.core.inventory_active                   = false;
            }
            game.core.io.key_i                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_b) // Skill book menu
        {
            if (!game.core.skillbook_active)
            {
                game.window_manager.window_enable(SKILLBOOK_UID);
                game.core.skillbook_active                   = true;
            }
            else
            {
                game.window_manager.window_disable(SKILLBOOK_UID);
                game.core.skillbook_active                   = false;
            }
            game.core.io.key_b                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_space) // close all open windows
        {
            if (game.core.game_menu_active)
            {
                game.window_manager.window_disable(MENU_MAIN_UID);
                game.core.game_menu_active                   = false;
            }
            if (game.core.equipment_active)
            {
                game.window_manager.window_disable(EQUIPMENT_UID);
                game.core.equipment_active                   = false;
            }
            if (game.core.quest_log_active)
            {
                game.window_manager.window_disable(QUEST_LOG_UID);
                game.core.quest_log_active                   = false;
            }
            if (game.core.character_active)
            {
                game.window_manager.window_disable(CHARACTER_UID);
                game.core.character_active                   = false;
            }
            if (game.core.inventory_active)
            {
                game.window_manager.window_disable(INVENTORY_UID);
                game.core.inventory_active                   = false;
            }
            if (game.core.skillbook_active)
            {
                game.window_manager.window_disable(SKILLBOOK_UID);
                game.core.skillbook_active                   = false;
            }
            if (game.core.npcvendor_active)
            {
                game.window_manager.window_disable(NPCVENDOR_UID);
                game.core.npcvendor_active                   = false;
            }
            game.core.io.key_space                 = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_alt) // display item names on map (loot / click-able items)
        {
            game.core.io.key_alt                   = false;
            game.core.io.keyboard_delay_count      = 0;
        }
///------------------------------------------------------------------------------------------
        if (game.core.io.key_r) // regenerate random map.
        {
            game.map_2D.random_map(100,100,CAVE,DUNGEON);
            //zoom out for testing
            game.zoom.current = game.zoom.max;
            game.map_2D.calculate_tile_positions(DEFAULT_FRAME_WIDTH/game.zoom.current/2.0f,DEFAULT_FRAME_HEIGHT/game.zoom.current/2.0f);
           //game.resource.sound.menu_select_00.play();
            game.core.io.key_r                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_d) // toggle debug.
        {
            game.debug = !game.debug;
            game.core.io.key_d                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
        if (game.core.io.key_t) // test exp++
        {
            game.player.level.current_experience++;
            game.core.io.key_t                     = false;
            game.core.io.keyboard_delay_count      = 0;
        }
    }
///------------------------------------------------------------------------------------------
};

void game_class::render(void)
{
    /*
    if (game.world_ambient.increase) // day / night lighting
    {
        game.world_ambient.intensity_R += game.world_ambient.speed;
        game.world_ambient.intensity_G += game.world_ambient.speed;
        game.world_ambient.intensity_B += game.world_ambient.speed;
        if (game.world_ambient.intensity_R > game.global_ambient.intensity_R) game.world_ambient.increase = false;
    }
    if (!game.world_ambient.increase)
    {
        game.world_ambient.intensity_R -= game.world_ambient.speed;
        game.world_ambient.intensity_G -= game.world_ambient.speed;
        game.world_ambient.intensity_B -= game.world_ambient.speed;
        if (game.world_ambient.intensity_R < -0.5f) game.world_ambient.increase = true;
    }
    */
    float  global_ambient_light[] = {game.global_ambient.intensity_R,game.global_ambient.intensity_G,game.global_ambient.intensity_B,game.global_ambient.intensity_A};
    float  world_ambient_light[]  = {game.world_ambient.intensity_R,game.world_ambient.intensity_G,game.world_ambient.intensity_B,game.world_ambient.intensity_A};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,world_ambient_light);

    game.map_2D.render();
    //game.resource.map_3D.town.draw();
    game.player.render();
    game.npc.render();

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient_light);
    game.window_manager.render();
};

