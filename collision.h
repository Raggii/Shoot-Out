/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for checking collisions between Dots and Players
*/

#ifndef COLLISION_H
#define COLLISION_H

/* Includes */
#include "tinygl.h"
#include "player_controller.h"
#include "dot_drop.h"

/* Functions  */
/**
Checks if the x corrdiant of the player is equal to the dot
@param player is a tinygl_point_t that holds the current x y position for the player
@param current_dot holds the current timer score for the player
*/
bool x_collision(Player * player, Dot * current_dot);

/**
* Checks if the y corrdiant of the player is equal to the dot
* @param player is a tinygl_point_t that holds the current x y position for the player
* @param current_dot holds the current timer score for the player
*/
bool y_collision(Player * player, Dot * current_dot);

/**
* Increases the amount of dots to come down, slowing down the progress of the player
* @param player is a tinygl_point_t that holds the current x y position for the player
* @param collision is a boolean Pointer Pointer which checks if a collision has occored
*/
void call_collision(Player * player, bool** collision);

/**
* Checks weather both the x and y cordiants are equal for the dot and the player
* if so a collision occored and the timer should be incremeneted.
* @param player is a tinygl_point_t that holds the current x y position for the player
* @param dot holds the current timer score for the player
* @param collision a boolean checking if a dot has collided or not
*/
void check_collision(Player * player, Dot * dot, bool* collision);

/** Checks for collision between the inputted dot and player
 * @param player A player pointer to check for collision
 * @param dot A dot pointer to check for coliision
 */
bool collision_occured(Player * player, Dot * dot);

/**
Check the given players health to see if the game is over
* @param player checks the player given from the main games counter to see if the game should be over
 */
bool is_player_finished(Player * player);

#endif
