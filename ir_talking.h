/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman
    @date 16 October 2020
    @brief module for controlling the dropping dot
*/

#ifndef IR_TALKING_H
#define IR_TALKING_H

/* Includes */
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include <stdlib.h>
#include "player_controller.h"
#include "ir_uart.h"
#include <stdbool.h>
#include "../fonts/font5x5_1.h"

/* Inital defines */
#define PACER_RATE 500 // the speed the pacer updates
#define MESSAGE_RATE 30 // the speed of the message updating
#define WIN_MESSAGE "You Win!" // The message displayed when a player won
#define LOSE_MESSAGE "You Lose!" // The message displayed when a player lost
#define WIN_CHAR 'W' // The char sent when a player won
#define LOSE_CHAR 'L' // The char sent when a player lost

/*Functions */

/**
Sends information to other board weather this board has finished
 */
void send_finish_game_info(void);

/**
 * displays the title screen message to the current board
 * @param player is a tinygl_point_t that holds the current x y position for the player
 */
void title_screen_display(Player* player);

/**
 * sents a given message onto the tinygl screen
 * @param message is the message to be displayed given as a char *
 */
void initialize_message(char * message);

/**
Gets the messgae from the finish and displays the given message
* @param finish_char is the char that decides if you win or lose l = lose w = win
* @param shot is a bool that is 1 if a shot is currently going and 0 otherwise
* @param drop is a bool that is 1 if a enemy dot is currently going and 0 otherwise
* @param player is a tinygl_point_t that holds the current x y position for the player
 */
void display_finish_message(char finish_char, bool* shot, bool* drop, Player* player);

#endif
