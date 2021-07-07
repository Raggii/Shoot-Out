/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for player controls and initilization
**/

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

/* Includes */
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include <stdlib.h>

/* Inital defines */
#define PACER_RATE 500 // speed of the pace refresh
#define LOOP_RATE 300 // amount of times it loops to update player
#define LEFT_SIDE 0 // The left side of the LED screen
#define RIGHT_SIDE 4 // the right side of the LED screen
#define INTIAL_PLAYER_POS 2 // The position the player is spawned at
#define BOTTOM 6 // The bottom of the LED screen
#define LED_ON 1 // The on state of an LED
#define LED_OFF 0 // The off state of an LED
#define MOVE_LEFT -1 // The direction and value of moving the player left
#define MOVE_RIGHT 1 // The direction and value of moving the player right
#define PLAYER_HEALTH 3 // The amount of health given to the player

/* Functions  */
/**
sturcture to hold the variables for the player charater
@param current_postion is a tinygl_point_t that holds the current x y position for the player
@param timer holds the current timer score for the player
*/
typedef struct player_holder
{
    tinygl_point_t current_position;
    int8_t health;
} Player;

/**
displays updated position of given player
@param player is a Player * that holds the current game charater
*/
void display_new_postion(Player * player);

/**
changes postion of player and turns off past light position
@param player is a Player * that holds the current game charater
@param x_change_amount is the amount of positions the charater will move in the x direction
*/
void change_player_position(Player* player, int8_t x_change_amount);

/**
makes new player pointer for initial position and returns it.
also turns on point for this position
@param health Gives the amount of hits the player can take
@return Returns the initilzed player as a Pointer
*/
Player * initilize_player(int8_t health);

/**
moves the player left by 1 value
@param player is a Player Structure for the current player
*/
void move_player_left(Player* player);

/**
Moves the player right by 1 value
@param player is a Player Structure for the current player
*/
void move_player_right(Player* player);

/** frees the memory taken by the player charater
 * @param player the player to be free
 */
void free_player(Player* player);

#endif
