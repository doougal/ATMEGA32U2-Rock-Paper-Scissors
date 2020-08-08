/*  #file   logic_handler.c
    #author Juliet Samandari (jsa117), Alex Burling (arb142) -group217
    #date   9 October 2019
    #desc   Helper file to handle game logic and decisions
*/

#include "system.h"
#include "logic_handler.h"
#include "display_handler.h"

#define ROCK_CHAR 'R'
#define PAPER_CHAR 'P'
#define SCISSORS_CHAR 'S'


/** compares the two input parameters to decide which player has won
 *  the round, call the appropriate display function,
 *  and return a state variable **/
int logic_check_round(char my_choice, uint8_t recieved_char)
{
    int win = 0;

    if (my_choice == ROCK_CHAR) {
        if (recieved_char == SCISSORS_CHAR) {
            display_round_win();
            win = 1;
        } else if (recieved_char == PAPER_CHAR) {
            display_round_lose();
            win = 2;
        } else {
            display_round_tie();
        }
    } else if (my_choice == PAPER_CHAR) {
        if (recieved_char == ROCK_CHAR) {
            display_round_win();
            win = 1;
        } else if (recieved_char == SCISSORS_CHAR) {
            display_round_lose();
            win = 2;
        } else {
            display_round_tie();
        }
    } else if (my_choice == SCISSORS_CHAR) {
        if (recieved_char == PAPER_CHAR) {
            display_round_win();
            win = 1;
        } else if (recieved_char == ROCK_CHAR) {
            display_round_lose();
            win = 2;
        } else {
            display_round_tie();
        }
    }

    return win;
}

/** compares the three input parameters to decide if the game is over,
 *  which player has won, call the appropriate display function,
 *  and return a state variable **/
int logic_check_game(int local_score, int remote_score, int round_limit)
{
    int game_over = 0;

    if (local_score >= round_limit) {
        display_game_win(local_score, remote_score);
        game_over = 1;
    } else if (remote_score >= round_limit) {
        display_game_lose(local_score, remote_score);
        game_over = 1;
    }

    return game_over;
}

