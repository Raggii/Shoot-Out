/** @file player_controller.h
    @author J. A. Allred, UC Student & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for controlling the dropping dot
*/

/* Includes */
#include <time.h>
#include <stdlib.h>
#include "dot_drop.h"
#include "system.h"
#include "button.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "player_controller.h"
#include "collision.h"
#include <stdbool.h>

/* Functions  */

/* turns on the led for the given positon of the dot */
void change_dot_coord(int8_t x, int8_t y, int8_t on_off)
{
    tinygl_draw_point (tinygl_point (x, y),on_off);
}


//Checks if the y coord can be increaced
// does not move it just checks and returns a boolean
bool check_increase_y (Dot* dot)
{
    return (dot->tick_counter >= DROP_TIME);
}

// increaces y pos by 1
void increace_y_coord(Dot* dot, int8_t direction)
{
    dot->tick_counter = INITAL_POSITION;
    //decrements the y position
    dot->y_coord += direction;
    //checks whether the dot goes below the finish point
    if (dot->y_coord == OFF_THE_BOARD) {
        dot->end_point += direction;
    }
}

//changes the x coord to the players x coord
void dot_coord_to_player_coord(Player* player, Dot* dot)
{
    dot->x_coord = player->current_position.x;
}

// initilizes a given dot with x y endpoint and previous inputs
Dot * init_dot_dropper(int8_t y_coord, int8_t x_coord, int8_t endpoint, Dot* previous)
{
    Dot * dot = malloc(sizeof(Dot));
    dot->tick_counter = INITAL_POSITION;
    dot->y_coord = y_coord;
    dot->x_coord = x_coord;
    dot->end_point = endpoint;
    dot->previous_dot = previous;
    return dot;
}

// This function moves the bullet down by 1 dot
// When the timer is right this should be called only when counter is finished
void control_dot(Dot* dot_test, int8_t direction)
{
    increace_y_coord(dot_test, direction * REVERSE_DIRECTION);
    if (dot_test->y_coord < OFF_THE_BOARD) {
        change_dot_coord(dot_test->x_coord, dot_test->y_coord + direction, OFF);
    }
    if (dot_test->y_coord == dot_test->end_point) {
        //At the end of the drop
        change_dot_coord(dot_test->x_coord, dot_test->y_coord, OFF);
    }
    change_dot_coord(dot_test->x_coord, dot_test->y_coord, ON);
}

//Need a shoot function that starts at player and goes the whole way
//Button push can give a boolean to call a funciton
void send_dot_pos(int8_t x_coord)
{
    ir_uart_putc(x_coord);
}

//takes players position and starts a dot from its position
void shoot_dot_from_player( Dot* dot, bool* shot, int8_t x_coord)
{
    dot->tick_counter++;
    if(check_increase_y(dot)) {
        control_dot(dot, +1);
    }
    if (dot->y_coord == dot->end_point - 2) {
        send_dot_pos(x_coord);
        //shot has finished, now able to fire new shot
        *shot = 0;
        free_previous_dot(dot);
    }
}

//frees up memory of previous dot.
void free_previous_dot(Dot* dot)
{
    if (dot->previous_dot != NULL) {
        free(dot->previous_dot);
    }
}

//dropping the oposite shot by one
void dropping_dot(Dot* dot, bool* drop)
{
    dot->tick_counter++;
    if(check_increase_y(dot)) {
        control_dot(dot, -1);
    }
    if (dot->y_coord == dot->end_point + 1) {
        *drop = 0;
        if (dot->previous_dot != NULL) {
            free_previous_dot(dot);
        }
    }
}

//gets input from the game of the x coord of the shot dot and creates a new dot there
Dot* recv_dot_pos(Dot* previous_drop, int8_t x_coord)
{
    Dot* dot = init_dot_dropper(TOP_LED, x_coord, BOTTOM_LED, previous_drop);
    return dot;
}



