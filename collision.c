/** @file player_controller.h
    @author J. A. Allred, UC Student & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for checking collisions between Dots and Players
*/

/* Includes */
#include "system.h"
#include "button.h"
#include "pacer.h"
#include <stdlib.h>
#include "ir_uart.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "player_controller.h"
#include "dot_drop.h"
#include <stdbool.h>
#include "collision.h"

/* Functions */

//Checks if the x corrdiant of the player is equal to the dot
bool x_collision(Player * player, Dot * current_dot)
{
    bool return_x_col = player->current_position.x == current_dot->x_coord;
    return return_x_col;
}

//Checks if the y corrdiant of the player is equal to the dot
bool y_collision(Player * player, Dot * current_dot)
{
    return player->current_position.y == current_dot->y_coord;
}

//Increases the amount of dots to come down, slowing down the progress of the player
void call_collision(Player * player, bool** collision)
{
    if (**collision == 0) {
        player->health -= 1;
        **collision = 1;
    }
}

// Checks weather both the x and y cordiants are equal for the dot and the player
// if so a collision occored and the timer should be incremeneted.
void check_collision(Player * player, Dot * dot, bool* collision)
{
    if(collision_occured(player, dot)) {
        call_collision(player, &collision);
    }
}

// Checks for a collision between the player and the dot
bool collision_occured(Player* player, Dot* dot)
{
    return x_collision(player, dot) && y_collision(player, dot);
}

// Check the given players health to see if the game is over
bool is_player_finished(Player * player)
{
    return player->health <= 0;
}


