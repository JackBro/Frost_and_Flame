/**
 * Copyright (C) 2011 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
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

#include "UI.hpp"
#include "game.hpp"

extern game_type game;

//----------------------------------------------------------------------------------------------------------------

    player_stats_class::player_stats_class(void)
{
    player_stats_class::highlighted      = false;
    player_stats_class::drag             = false;
    player_stats_class::portrait         = 0;
    player_stats_class::mouse_over_count = 0;
    player_stats_class::tooltip_time     = 128;
    player_stats_class::tooltip_active   = false;
    player_stats_class::pos_x            = 0.0f;
    player_stats_class::pos_y            = 0.0f;
    player_stats_class::pos_z            = 0.0f;
    player_stats_class::width            = 0.0f;
    player_stats_class::height           = 0.0f;
};

    player_stats_class::~player_stats_class(void)
{

};

void player_stats_class::process(void)
{

    //if mouse_over, drag, tool_tip etc...
};

void player_stats_class::draw(void)
{
    float temp_float = 0.0f;
    game.texture.profile_background.draw(false,player_stats_class::pos_x-(player_stats_class::width/3.3f),player_stats_class::pos_y,player_stats_class::pos_z,player_stats_class::width/2.8f,player_stats_class::height/1.1f);
    game.texture.profile_main_background.draw(false,player_stats_class::pos_x,player_stats_class::pos_y,player_stats_class::pos_z,player_stats_class::width,player_stats_class::height);
    temp_float = ((player_stats_class::width/1.8f)*((float)game.player.health.current/(float)game.player.health.maximum));
    game.texture.health_bar.draw(false,player_stats_class::pos_x-(player_stats_class::width/8.0f)+(temp_float/2),player_stats_class::pos_y+(player_stats_class::height/3.6f),player_stats_class::pos_z,temp_float,player_stats_class::height/6.2f);
    temp_float = ((player_stats_class::width/1.8f)*((float)game.player.mana.current/(float)game.player.mana.maximum));
    game.texture.mana_bar.draw(false,player_stats_class::pos_x-(player_stats_class::width/8.0f)+(temp_float/2),player_stats_class::pos_y+(player_stats_class::height/9.0f),player_stats_class::pos_z,temp_float,player_stats_class::height/6.2f);
    game.texture.profile_main.draw(false,player_stats_class::pos_x,player_stats_class::pos_y,player_stats_class::pos_z,player_stats_class::width,player_stats_class::height);
};

//----------------------------------------------------------------------------------------------------------------

    action_slot_class::action_slot_class(void)
{
    action_slot_class::highlighted      = false;
    action_slot_class::drag             = false;
    action_slot_class::button_type      = 0;
    action_slot_class::mouse_over       = false;
    action_slot_class::mouse_over_count = 0;
    action_slot_class::tooltip_time     = 128;
    action_slot_class::tooltip_active   = false;
    action_slot_class::pos_x            = 0.0f;
    action_slot_class::pos_y            = 0.0f;
    action_slot_class::pos_z            = 0.0f;
    action_slot_class::width            = 0.0f;
    action_slot_class::height           = 0.0f;
};

    action_slot_class::~action_slot_class(void)
{

};

void action_slot_class::process(void)
{
    if (game.core.physics.point_in_quadrangle(action_slot_class::pos_x,action_slot_class::width,action_slot_class::pos_y,action_slot_class::height,game.core.io.mouse_x,game.core.io.mouse_y)) action_slot_class::mouse_over = true;
    else action_slot_class::mouse_over = false;
    //if mouse_over, drag, tool_tip etc...
};

void action_slot_class::draw(void)
{
    if (action_slot_class::button_type == 1) game.texture.icon_melee.draw(false,action_slot_class::pos_x,action_slot_class::pos_y,action_slot_class::pos_z,action_slot_class::width,action_slot_class::height);

    game.texture.glass_cover_01.draw(false,action_slot_class::pos_x,action_slot_class::pos_y,action_slot_class::pos_z,action_slot_class::width,action_slot_class::height);
};

void action_slot_class::draw_tooltip(void)
{

};

//----------------------------------------------------------------------------------------------------------------

    menu_slot_class::menu_slot_class(void)
{
    menu_slot_class::highlighted      = false;
    menu_slot_class::drag             = false;
    menu_slot_class::button_type      = 0;
    menu_slot_class::mouse_over       = false;
    menu_slot_class::mouse_over_count = 0;
    menu_slot_class::tooltip_time     = 128;
    menu_slot_class::tooltip_active   = false;
    menu_slot_class::pos_x            = 0.0f;
    menu_slot_class::pos_y            = 0.0f;
    menu_slot_class::pos_z            = 0.0f;
    menu_slot_class::width            = 0.0f;
    menu_slot_class::height           = 0.0f;
};

    menu_slot_class::~menu_slot_class(void)
{

};

void menu_slot_class::process(void)
{
    //if mouse_over, drag, etc...
    if (menu_slot_class::mouse_over) menu_slot_class::mouse_over_count++;
    else menu_slot_class::mouse_over_count = 0;
    if (menu_slot_class::mouse_over_count > 65530) menu_slot_class::mouse_over_count = 65530;
    if (game.core.physics.point_in_circle(menu_slot_class::pos_x,menu_slot_class::pos_y,(menu_slot_class::height/2),game.core.io.mouse_x,game.core.io.mouse_y)) menu_slot_class::mouse_over = true;
    else menu_slot_class::mouse_over = false;
    if ((menu_slot_class::mouse_over) && (game.core.io.mouse_button_left))
    {
        switch (menu_slot_class::button_type) // process mouse click
        {
            case 1: // main menu
                if (!game.core.menu_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.menu_level              = 1;
                    game.core.menu_active             = true;
                    game.core.io.escape               = false;
                    game.core.io.keyboard_delay_count = 0;
                    game.core.config.menu_delay_count = 0;
                }
            break;
            case 2: // NA??
                if (!game.core.menu_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.menu_level              = 1;
                    game.core.menu_active             = true;
                    game.core.io.escape               = false;
                    game.core.io.keyboard_delay_count = 0;
                    game.core.config.menu_delay_count = 0;
                }
            break;
            case 3: // Quest Log
                if (!game.core.questbook_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.questbook_active        = true;
                }
            break;
            case 4: // Character Menu
                if (!game.core.character_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.character_active        = true;
                }
            break;
            case 5: // Inventory
                if (!game.core.inventory_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.inventory_active        = true;
                }
            break;
            case 6: // Spell Book
                if (!game.core.spellbook_active)
                {
                    game.sound.menu_select_00.play();
                    game.core.spellbook_active        = true;
                }
            break;
            default:
            break;
        }
    }
    if ((menu_slot_class::mouse_over) && (game.core.io.mouse_button_right))//drag
    {
        ;
    }
};

void menu_slot_class::draw(void)
{
    if (menu_slot_class::button_type == 1) game.texture.icon_01.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    if (menu_slot_class::button_type == 2) game.texture.icon_02.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    if (menu_slot_class::button_type == 3) game.texture.icon_03.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    if (menu_slot_class::button_type == 4) game.texture.icon_04.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    if (menu_slot_class::button_type == 5) game.texture.icon_05.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    if (menu_slot_class::button_type == 6) game.texture.icon_06.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
    game.texture.glass_cover_02.draw(false,menu_slot_class::pos_x,menu_slot_class::pos_y,menu_slot_class::pos_z,menu_slot_class::width,menu_slot_class::height);
};

void menu_slot_class::draw_tooltip(void)
{
    if (menu_slot_class::mouse_over_count > menu_slot_class::tooltip_time)
    {
        switch (menu_slot_class::button_type) // display tool tip
        {
            case 1: // main menu
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.main_menu);
            break;
            case 2: // NA??
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.menu_item_unavailable);
            break;
            case 3: // Quest Log
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.quest_log);
            break;
            case 4: // Character Menu
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.character_menu);
            break;
            case 5: // Inventory
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.inventory);
            break;
            case 6: // Spell Book
                game.font.font_1.Write(255,255,255,255,game.core.io.mouse_x,game.core.io.mouse_y,4.8f,32.0f,game.language.text.spell_book);
            default:
            break;
        }
    }
};

//----------------------------------------------------------------------------------------------------------------

    action_bar_class::action_bar_class(void)
{
    action_bar_class::pos_x            = 0.0f;
    action_bar_class::pos_y            = 0.0f;
    action_bar_class::pos_z            = 0.0f;
    action_bar_class::width            = 0.0f;
    action_bar_class::height           = 0.0f;
};

    action_bar_class::~action_bar_class(void)
{

};

void action_bar_class::process(void)
{
    action_bar_class::menu_slot_01.process();
    action_bar_class::menu_slot_02.process();
    action_bar_class::menu_slot_03.process();
    action_bar_class::menu_slot_04.process();
    action_bar_class::menu_slot_05.process();
    action_bar_class::menu_slot_06.process();
    action_bar_class::action_slot_01.process();
    action_bar_class::action_slot_02.process();
    action_bar_class::action_slot_03.process();
    action_bar_class::action_slot_04.process();
    action_bar_class::action_slot_05.process();
    action_bar_class::action_slot_06.process();
    action_bar_class::action_slot_07.process();
    action_bar_class::action_slot_08.process();
    action_bar_class::action_slot_09.process();
    action_bar_class::action_slot_10.process();
};

void action_bar_class::draw(void)
{
    game.texture.action_bar.draw(false,action_bar_class::pos_x,action_bar_class::pos_y,action_bar_class::pos_z,action_bar_class::width,action_bar_class::height);
    action_bar_class::action_slot_01.draw();
    action_bar_class::action_slot_02.draw();
    action_bar_class::action_slot_03.draw();
    action_bar_class::action_slot_04.draw();
    action_bar_class::action_slot_05.draw();
    action_bar_class::action_slot_06.draw();
    action_bar_class::action_slot_07.draw();
    action_bar_class::action_slot_08.draw();
    action_bar_class::action_slot_09.draw();
    action_bar_class::action_slot_10.draw();
    game.texture.action_bar_front.draw(false,action_bar_class::pos_x,action_bar_class::pos_y,action_bar_class::pos_z,action_bar_class::width,action_bar_class::height);
    action_bar_class::menu_slot_01.draw();
    action_bar_class::menu_slot_02.draw();
    action_bar_class::menu_slot_03.draw();
    action_bar_class::menu_slot_04.draw();
    action_bar_class::menu_slot_05.draw();
    action_bar_class::menu_slot_06.draw();
    action_bar_class::menu_slot_01.draw_tooltip();
    action_bar_class::menu_slot_02.draw_tooltip();
    action_bar_class::menu_slot_03.draw_tooltip();
    action_bar_class::menu_slot_04.draw_tooltip();
    action_bar_class::menu_slot_05.draw_tooltip();
    action_bar_class::menu_slot_06.draw_tooltip();
    action_bar_class::action_slot_01.draw_tooltip();
    action_bar_class::action_slot_02.draw_tooltip();
    action_bar_class::action_slot_03.draw_tooltip();
    action_bar_class::action_slot_04.draw_tooltip();
    action_bar_class::action_slot_05.draw_tooltip();
    action_bar_class::action_slot_06.draw_tooltip();
    action_bar_class::action_slot_07.draw_tooltip();
    action_bar_class::action_slot_08.draw_tooltip();
    action_bar_class::action_slot_09.draw_tooltip();
    action_bar_class::action_slot_10.draw_tooltip();
};

//----------------------------------------------------------------------------------------------------------------
    UI_class::UI_class(void)
{
    game.UI.action_bar.width                      =  1.2f;
    game.UI.action_bar.height                     =  game.UI.action_bar.width/10.0f;
    game.UI.action_bar.pos_x                      =  0.0f;
    game.UI.action_bar.pos_y                      = -1.0f + (game.UI.action_bar.height/2);
    game.UI.action_bar.pos_z                      =  0.001f;

    game.UI.action_bar.menu_slot_01.button_type   =  1;
    game.UI.action_bar.menu_slot_01.pos_x         =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/2.282f);
    game.UI.action_bar.menu_slot_01.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_01.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_01.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_01.height        =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_02.button_type   =  2;
    game.UI.action_bar.menu_slot_02.pos_x         =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/2.620f);
    game.UI.action_bar.menu_slot_02.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_02.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_02.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_02.height        =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_03.button_type   =  3;
    game.UI.action_bar.menu_slot_03.pos_x         =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/3.062f);
    game.UI.action_bar.menu_slot_03.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_03.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_03.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_03.height        =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_04.button_type   =  4;
    game.UI.action_bar.menu_slot_04.pos_x         =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/3.010f);
    game.UI.action_bar.menu_slot_04.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_04.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_04.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_04.height        =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_05.button_type   =  5;
    game.UI.action_bar.menu_slot_05.pos_x         =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/2.572f);
    game.UI.action_bar.menu_slot_05.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_05.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_05.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_05.height        =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_06.button_type   =  6;
    game.UI.action_bar.menu_slot_06.pos_x         =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/2.250f);
    game.UI.action_bar.menu_slot_06.pos_y         = -1.0f + (game.UI.action_bar.height/2.4);
    game.UI.action_bar.menu_slot_06.pos_z         =  game.UI.action_bar.pos_z;
    game.UI.action_bar.menu_slot_06.width         =  game.UI.action_bar.height/2.34f;
    game.UI.action_bar.menu_slot_06.height        =  game.UI.action_bar.height/2.34f;

    game.UI.action_bar.action_slot_01.button_type =  0;
    game.UI.action_bar.action_slot_01.pos_x       =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/3.970f);
    game.UI.action_bar.action_slot_01.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_01.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_01.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_01.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_02.button_type =  0;
    game.UI.action_bar.action_slot_02.pos_x       =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/5.100f);
    game.UI.action_bar.action_slot_02.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_02.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_02.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_02.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_03.button_type =  0;
    game.UI.action_bar.action_slot_03.pos_x       =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/7.120f);
    game.UI.action_bar.action_slot_03.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_03.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_03.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_03.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_04.button_type =  0;
    game.UI.action_bar.action_slot_04.pos_x       =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/12.000f);
    game.UI.action_bar.action_slot_04.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_04.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_04.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_04.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_05.button_type =  0;
    game.UI.action_bar.action_slot_05.pos_x       =  game.UI.action_bar.pos_x - (game.UI.action_bar.width/36.600f);
    game.UI.action_bar.action_slot_05.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_05.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_05.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_05.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_06.button_type =  0;
    game.UI.action_bar.action_slot_06.pos_x       =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/35.000f);
    game.UI.action_bar.action_slot_06.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_06.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_06.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_06.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_07.button_type =  0;
    game.UI.action_bar.action_slot_07.pos_x       =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/11.700f);
    game.UI.action_bar.action_slot_07.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_07.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_07.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_07.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_08.button_type =  0;
    game.UI.action_bar.action_slot_08.pos_x       =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/7.060f);
    game.UI.action_bar.action_slot_08.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_08.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_08.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_08.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_09.button_type =  0;
    game.UI.action_bar.action_slot_09.pos_x       =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/5.054f);
    game.UI.action_bar.action_slot_09.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_09.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_09.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_09.width       =  game.UI.action_bar.action_slot_01.height/1.450f;
    game.UI.action_bar.action_slot_10.button_type =  1;
    game.UI.action_bar.action_slot_10.pos_x       =  game.UI.action_bar.pos_x + (game.UI.action_bar.width/3.940f);
    game.UI.action_bar.action_slot_10.pos_y       = -1.0f + (game.UI.action_bar.height/2.00f);
    game.UI.action_bar.action_slot_10.pos_z       =  game.UI.action_bar.pos_z;
    game.UI.action_bar.action_slot_10.height      =  game.UI.action_bar.height/1.34f;
    game.UI.action_bar.action_slot_10.width       =  game.UI.action_bar.action_slot_01.height/1.450f;

    game.UI.player_stats.portrait                 =  0;
    game.UI.player_stats.pos_x                    = -0.8f;
    game.UI.player_stats.pos_y                    =  0.88f;
    game.UI.player_stats.pos_z                    =  0.001f;
    game.UI.player_stats.width                    =  0.4f;
    game.UI.player_stats.height                   =  0.24f;
};

    UI_class::~UI_class(void)
{

};

void UI_class::process(void)
{
    UI_class::player_stats.process();
    UI_class::action_bar.process();
};

void UI_class::draw(void)
{
    UI_class::player_stats.draw();
    UI_class::action_bar.draw();
};

