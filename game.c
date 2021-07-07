/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman 58211557
    @date 16 October 2020
    @brief the executable file for the game to run
**/

/* Includes */
#include "system.h"
#include "dot_drop.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "collision.h"
#include <stdlib.h>
#include "../fonts/font5x5_1.h"
#include "ir_talking.h"
#include "player_controller.h"
#include "button.h"

/* Defines */
#define ON  1 // The state of an on
#define OFF  0 // the state of an off
#define TICK_COUNTER_INITIAL 0 // The initial value for the tick counter

/* Funcitons */

// This initilizes the system, the tinygl, the pacer, the navswitch and the Ir moduals.
void init_all(void)
{
    system_init();
    tinygl_init (500);
    pacer_init (500);
    navswitch_init ();
    ir_uart_init();
    button_init();
}

// Updates the pacer the tinygl and the navswtch
void update_all(void)
{
    pacer_wait ();
    tinygl_update ();
    navswitch_update();
    button_update();
}

//starts the game
int main (void)
{
    init_all();
    Player * player = initilize_player(PLAYER_HEALTH); // given 1 health
    bool shot = 0;
    //Drop is 1 if there are shots from the otherplayer currently on thier screen, 0 otherwise
    bool drop = 0;
    //collision 1 if there is a collisoin and 0 otherwise.
    bool collision = 0;
    int8_t x_coord = 0;
    // this holds the information from the ir read function as when read it removes it from the buffer
    //Holds '0' as an initial value as nothing
    char check = '0';
    tinygl_font_set(&font5x5_1);
    title_screen_display(player);
    Dot * dot = init_dot_dropper(BOTTOM_LED, TICK_COUNTER_INITIAL, TOP_LED, NULL);
    Dot * dot_enemy = init_dot_dropper(TOP_LED, TICK_COUNTER_INITIAL, BOTTOM_LED, NULL);
    while (1) {
        update_all();
        /* checking for inputs from the player */
        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            move_player_left(player);
        } else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            move_player_right(player);
        } else if(navswitch_push_event_p(NAVSWITCH_PUSH) && shot == 0) {
            //creates new dot
            dot = init_dot_dropper(BOTTOM_LED, 0, TOP_LED, dot);
            //sets position
            dot_coord_to_player_coord(player, dot);
            x_coord = player->current_position.x;
            // puts the bullet one higher than the player to start
            dot->y_coord -= 1;
            // means that a shot has started
            shot = 1;
        }
        // Checks the positon of the dot
        if (shot == 1) {
            //increments the shot by one if there is a shot going
            shoot_dot_from_player(dot, &shot, x_coord);
        }
        //When information is received in the buffer checks if its a bullet or a end game
        if(ir_uart_read_ready_p()) {
            check = ir_uart_getc();
            if(check == 'W') {
                display_finish_message(check, &shot, &drop, player);
            } else {
                collision = 0;
                dot_enemy = recv_dot_pos(dot_enemy, check);
                //means that the drop of dot has started
                drop = 1;
            }
        }
        if (drop == 1) {
            //drop the dot by one
            dropping_dot(dot_enemy, &drop);
        }
        check_collision(player, dot_enemy, &collision);
        if(is_player_finished(player)) {
            //so the player is dead if its here so send data to other player saying they have won the game
            send_finish_game_info();// as they have lost a "W" char is sent to the other player
            display_finish_message('L', &shot, &drop, player);// as they have lost it will display the losing char to this player
        }
        display_new_postion(player);
    }
}
