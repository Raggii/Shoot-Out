/** @file player_controller.h
    @author J. A. Allred, 36715295 & W. M. Stedman 58211557
    @date 16 October 2020
    @brief module for controlling the finishing IR talking between boards
*/
/* Includes */
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include <stdlib.h>
#include "player_controller.h"
#include "ir_uart.h"
#include <stdbool.h>
#include "../fonts/font5x5_1.h"
#include "ir_talking.h"
#include "button.h"
#include "navswitch.h"

/* Funcitons */

// Puts the given message onto the games scrolling text
void initialize_message(char * message)
{
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
}

//waits for either player to push the start button and breaks the loop
//when this happends
static void screen_wait(Player * player)
{
    bool ready_to_start = 0;
    while(!ready_to_start) {
        if(button_push_event_p(0)) {
            ready_to_start = 1;
        }
        pacer_wait ();
        tinygl_update ();
        navswitch_update();
        button_update();
    }
    navswitch_update();
    tinygl_clear();
    display_new_postion(player);
}

//Sends information to other board weather this board has finished
void send_finish_game_info(void)
{
    ir_uart_putc(WIN_CHAR);
}

//Gets the messgae from the finish and displays the given message
void display_finish_message(char finish_char, bool* shot, bool* drop, Player* player)
{
    char * message = "ERROR DID NOT FIND CORRECT CHAR";
    if(finish_char == WIN_CHAR) {
        message = WIN_MESSAGE;
    } else if(finish_char == LOSE_CHAR) {
        message = LOSE_MESSAGE;
    }
    initialize_message(message);
    *shot = 0;
    *drop = 0;
    player->health = PLAYER_HEALTH;
    screen_wait(player);
}

//Displays the title screen promiting the player to click the button to start
void title_screen_display(Player* player)
{
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("CLICK TO START");
    screen_wait(player);
}
