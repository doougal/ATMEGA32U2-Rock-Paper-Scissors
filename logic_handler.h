/*  #file   logic_handler.h
    #author Juliet Samandari (jsa117), Alex Burling (arb142) -group217
    #date   9 October 2019
    #desc   Helper file to handle game logic and decisions
*/

#ifndef LOGIC_HANDLER_H
#define LOGIC_HANDLER_H

#include "system.h"
#include "display_handler.h"

/** compares the two input parameters to decide which player has won
 *  the round, call the appropriate display function,
 *  and return a state variable **/
int logic_check_round(char mychoice, uint8_t recievedc);

/** compares the three input parameters to decide if the game is over,
 *  which player has won, call the appropriate display function,
 *  and return a state variable **/
int logic_check_game(int local_score, int remote_score, int round_limit);

#endif
