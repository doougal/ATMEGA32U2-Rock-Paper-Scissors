/*  #file   game.c
    #author Juliet Samandari (jsa117), Alex Burling (arb142) -group217
    #date   2 October 2019
    #desc   A Rock Paper Scissors game!
*/

#include <stdbool.h>
#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "led.h"
#include "ledmat.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "display_handler.h"
#include "logic_handler.h"


#define PACER_RATE 500
#define TEXT_SPEED 30
#define LOOP_RATE 300
#define IR_SEND_RATE 20
#define TINYGL_FONT &font5x7_1
#define ROCK_CHAR 'R'
#define PAPER_CHAR 'P'
#define SCISSORS_CHAR 'S'


typedef enum {STATE_INIT, STATE_START, STATE_TITLE_WAIT, STATE_MODE_SELECT, STATE_PLAYING,
              STATE_OVER, STATE_SCORE, STATE_ROUND_END, STATE_GAME_END
             } state_t;

/**initialises the atmega32u2 and relevant interfaces**/
void board_init(void)
{
    system_init ();
    led_init ();
    navswitch_init ();
    ir_uart_init();
    ledmat_init();
    button_init();
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE);
    tinygl_font_set (TINYGL_FONT);
    tinygl_text_speed_set (TEXT_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    led_set(LED1, 1);
}

/**handles changing indicies when "scrolling" options**/
int navswitch_scroller(int choice_index)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        if (choice_index == 2) {
            choice_index = 0;
        } else {
            choice_index++;
        }
    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (choice_index == 0) {
            choice_index = 2;
        } else {
            choice_index--;
        }
    }
    return choice_index;
}

/**returns the round limit for the given choice_index**/
int set_round_limit(int choice_index)
{
    switch (choice_index) {
    default:
        return 3;

    case 1:
        return 5;

    case 2:
        return 7;
    }
}

/**updates the display if there is a change in choice_index**/
int change_game_mode(int choice_index)
{
    int prev_index = choice_index;
    choice_index = navswitch_scroller(choice_index);
    if (prev_index != choice_index) {
        switch (choice_index) {
        default:
            break;

        case 0:
            display_mode_three();
            break;

        case 1:
            display_mode_five();
            break;

        case 2:
            display_mode_seven();
            break;
        }
    }
    return choice_index;
}

/**resets the game back to initialisation state**/
state_t game_reset(void)
{
    led_set(LED1, 0);
    tinygl_clear();
    return STATE_INIT;
}

/**main funtion enabling game play**/
int main (void)
{
    state_t state = STATE_INIT;
    int choice_index = 0;
    char RPS[3] = {ROCK_CHAR, PAPER_CHAR, SCISSORS_CHAR};
    char RPS_choice = RPS[choice_index];
    uint8_t data = '\0';
    char final_choice = '\0';
    int round_limit = 0;
    int local_score = 0;
    int remote_score = 0;
    char win_state = 0;
    bool game_over = 0;
    bool ir_received = 0;
    bool ir_sent = 0;
    int round_end = 0;


    while (1) {

        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        button_update ();

        if (button_push_event_p(0)) { //restarts the game when button is pushed
            state = game_reset();
            remote_score = 0;
            local_score = 0;
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) { //shows the score when navswitch pushed east
            tinygl_clear();
            state = STATE_OVER;
        }

        switch (state) {

        default:
            break;

        case STATE_INIT: //initializes the board
            board_init();
            state = STATE_START;
            break;

        case STATE_START: //sets tinygl text to titlescreen
            display_title();
            state = STATE_TITLE_WAIT;
            break;

        case STATE_TITLE_WAIT: //displays titlescreen and waits for navswitch input
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                tinygl_clear();
                state = STATE_MODE_SELECT;
                display_mode_three();
            }
            break;

        case STATE_MODE_SELECT: //displays the gamemode selector and waits for navswitch input
            choice_index = change_game_mode(choice_index);
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                tinygl_clear();
                tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
                ir_uart_putc(choice_index);
                round_limit = set_round_limit(choice_index);
                state = STATE_PLAYING;
            }

            if (ir_uart_read_ready_p () ) {
                choice_index = ir_uart_getc();
                if (choice_index == 0 || choice_index == 1 || choice_index == 2) {
                    round_limit = set_round_limit(choice_index);
                    state = STATE_PLAYING;
                }
            }
            break;

        case STATE_PLAYING: //displays character options, waits for navswitch input, sends and receives
            if (ir_sent == 0) {
                choice_index = navswitch_scroller(choice_index);
                RPS_choice = RPS[choice_index];
                display_character(RPS_choice);
            }

            if (navswitch_push_event_p (NAVSWITCH_PUSH) && ir_sent == 0) {
                final_choice = RPS_choice;
                ir_uart_putc(final_choice);
                tinygl_clear();
                ir_sent = 1;
            }

            if (ir_uart_read_ready_p () && ir_received == 0) {
                data = ir_uart_getc ();
                if (data == ROCK_CHAR || data == PAPER_CHAR || data == SCISSORS_CHAR) { //checks valid input
                    display_character(data);
                    ir_received = 1;
                } else {
                    data = '\0';
                    ir_received = 0;
                }
            }
            if (ir_sent == 1 && ir_received == 1) {
                win_state = logic_check_round(final_choice, data);
                state = STATE_OVER;
            }
            break;


        case STATE_OVER: //calculates the score
            if (win_state == 0) {
                win_state = 3;

            } else if (win_state == 1) {
                local_score++;
                win_state = 3;

            } else if (win_state == 2) {
                remote_score++;
                win_state = 3;

            }

            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                tinygl_clear();
                display_score(local_score, remote_score);
                state = STATE_SCORE;
            }
            break;

        case STATE_SCORE: //displays the score
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                tinygl_clear();
                game_over = logic_check_game(local_score, remote_score, round_limit);
                if (game_over) {
                    state = STATE_GAME_END;
                } else {
                    state = STATE_ROUND_END;
                }
            }
            break;

        case STATE_ROUND_END: //restarts game to continue next round
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                round_end = 1;
                ir_uart_putc(round_end);
            }

            if (ir_uart_read_ready_p()) {
                round_end = ir_uart_getc();
            }

            if (round_end == 1) {
                tinygl_clear();
                data = '\0';
                final_choice = '\0';
                ir_sent = 0;
                ir_received = 0;
                round_end = 0;
                state = STATE_PLAYING;
            }
            break;

        case STATE_GAME_END: //restarts game with new round
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                state = game_reset();
                local_score = 0;
                remote_score = 0;
            }
            break;
        }
    }
}
