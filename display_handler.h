/*  #file   display_handler.h
    #author Juliet Samandari (jsa117), Alex Burling (arb142) -group217
    #date   9 October 2019
    #desc   Helper file to handle changing the display
*/

#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include <stdio.h>
#include "system.h"
#include "tinygl.h"

/** updates tinygl with #defined game title**/
void display_title(void);

/** updates tinygl with #defined gamemode string**/
void display_mode_three(void);

/** updates tinygl with #defined gamemode string**/
void display_mode_five(void);

/** updates tinygl with #defined gamemode string**/
void display_mode_seven(void);

/** updates tinygl with #defined round win string**/
void display_round_win(void);

/** updates tinygl with #defined round lose string**/
void display_round_lose(void);

/** updates tinygl with #defined round tie string**/
void display_round_tie(void);

/** updates tinygl with formatted score string**/
void display_score(int local, int remote);

/** updates tinygl with formatted game win string**/
void display_game_win(int local, int remote);

/** updates tinygl with formatted game lose string**/
void display_game_lose(int local, int remote);

/** updates tinygl with formatted text buffer to display character**/
void display_character (char character);

#endif
