/** @file player_controller.h
    @author J. A. Allred, UC Student & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for controlling the dropping dot
*/

#ifndef DOT_DROP_H
#define DOT_DROP_H

/* includes */
#include <stdlib.h>
#include "system.h"
#include "tinygl.h"
#include "player_controller.h"

/* inital Defines */
#define ON  1 // The on state for an LED
#define OFF  0 // The off state for an LED
#define BOTTOM_LED 6 // the position of the bottom LEDs on the display
#define TOP_LED -1 // The position one above the Board for the top LED
#define OFF_THE_BOARD 8 // The position one below the board for the LED screen
#define INITAL_POSITION 0 // A starting position for a variable
#define DROP_TIME 50 // the speed at which the LED drops
#define MAX_LED_LENGTH 7 // The length of the LED screen from top to bottom
#define REVERSE_DIRECTION -1 // The diretion being inversed

/* Functions */

/**
* Checks if the x Coord of the player is equal to the dot
* @param tick_counter is the distance the dot has travelled from the top of the screen
* @param y_coord holds the current y Coord for the Dot
* @param x_coord holds the current x Coord for the Dot
* @param end_point holds the finish point for the dot
* @param previous_dot holds the last shot dot to be freed
*/
typedef struct dot_s {
    int8_t tick_counter;
    int8_t y_coord;
    int8_t x_coord;
    int8_t end_point;
    struct dot_s *previous_dot;
}Dot ;

/**
turns on the led at the given position
@param x is the distance the dot has travelled from the top of the screen
@param y holds the current y Coord for the Dot
@param onoff tells the Led to be in the off or on state
*/
void change_dot_coord(int8_t x, int8_t y, int8_t on_off);

/** checks wheather the y corrd can be increaced
 * @param dot is the dot being checked
 * @return returns boolean on if it can moved or not
 * */
bool check_increase_y(Dot* dot);

/**
 * generates a random number
 * @param dot is the struct for the current dot falling
 * @param direction gives the direction as either +/-1 depending on how it will change y
*/
void increase_y_coord(Dot* dot, int8_t direction);

/**
* changes the x Coord of the dot to the given player
* @param steve is the struct for the current player
* @param dot is the struct for the current dot falling
*/
void dot_coord_to_player_coord(Player* player, Dot* dot);

/**
* initilizes the dot value and returns a pointer to it
* @param y_coord the x coord for the dot to start at
* @param x_coord the x coord for the dot to start at
* @param endpoint the end point for the dot to finish
* @param previous the last dot dropped
* @return returns a Dot pointer to the new initilized Dot structure
*/
Dot* init_dot_dropper(int8_t y_coord, int8_t x_coord, int8_t endpoint, Dot* previous);

/**
* Controlers the given dot value
* @param dot_test the struct for the current dot falling
* @param direction the direction of the dropping dot
*/
void control_dot(Dot* dot_test, int8_t direction);

/** sends the other player the current position of the shot dot
 * @param x_coord the player struct who shot the dot
 */
void send_dot_pos(int8_t x_coord);

/**
* takes players position and starts a dot from there
* @param player the given player to shoot from
* @param dot_test the given dot to shoot
* @param shot is an int * which determines if the player can shoot
*/
void shoot_dot_from_player(Dot* dot, bool* shot, int8_t x_coord);

/**
 * recives the position of the shot dot from the other player
 * @param dot is the given to free from the previous dot
 * @param x_coord is the coord recived from the incoming bullet
 * @return returns the newly created dot
 */
Dot* recv_dot_pos(Dot* dot, int8_t x_coord);

/**
 * drops a dot from the top of the screen to the bottom
 * @param dot the given dot struct to drop
 * @param drop and int * which determines the droppage
 */
void dropping_dot(Dot* dot, bool* drop);

/**
 * frees the previous dot structs
 * @param dot is the dot to be freed
 */
void free_previous_dot(Dot* dot);


#endif

