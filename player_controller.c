/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for player controls and initilization
*/

/*Includes */
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include <stdlib.h>
#include "player_controller.h"

/* Functions  */

// displays updated position of given player
void display_new_postion(Player * player)
{
    tinygl_draw_point(tinygl_point (player->current_position.x, player->current_position.y), LED_ON);
}

//changes postion of player and turns off past light position
void change_player_position(Player* player, int8_t x_change_amount)
{
    //Turns off current position by drawing an off line from left to right on bottom of the screen
    tinygl_draw_line (tinygl_point (LEFT_SIDE, BOTTOM), tinygl_point (RIGHT_SIDE, BOTTOM), LED_OFF);
    player->current_position.x += x_change_amount;
    display_new_postion(player);
}

// makes new player pointer for initial position and returns it.
// also turns on LED point for this position
Player * initilize_player(int8_t health)
{
    Player * new_player = malloc(sizeof(Player));
    new_player->current_position.x = INTIAL_PLAYER_POS;
    new_player->current_position.y = BOTTOM;
    new_player->health = health;
    return new_player;
}

//moves the player left by 1 value
void move_player_left(Player* player)
{
    if(player->current_position.x != LEFT_SIDE) {
        change_player_position(player, MOVE_LEFT);
    }
}

//Moves the player right by 1 value
void move_player_right(Player* player)
{
    if(player->current_position.x != RIGHT_SIDE) {
        change_player_position(player, MOVE_RIGHT);
    }
}

// frees the player struct
void free_player(Player* player) {
    free(player);
}
