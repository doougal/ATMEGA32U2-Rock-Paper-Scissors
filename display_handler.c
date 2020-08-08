/*  #file   display_handler.c
    #author Juliet Samandari (jsa117), Alex Burling (arb142) -group217
    #date   9 October 2019
    #desc   Helper file to handle changing the display
*/

#include <stdio.h>
#include "system.h"
#include "display_handler.h"

#define TITLE_SCREEN_STRING " ROCK PAPER SCISSORS PUSH START"
#define MODE_THREE_STRING " FIRST TO THREE"
#define MODE_FIVE_STRING " FIRST TO FIVE"
#define MODE_SEVEN_STRING " FIRST TO SEVEN"
#define ROUND_WIN_STRING " YOU WIN!"
#define ROUND_LOSE_STRING " YOU LOSE"
#define TIE_STRING " TIE"
#define SCORE_STRING " %i TO %i"
#define GAME_WIN_STRING " GAME OVER YOU WON %i TO %i"
#define GAME_LOSE_STRING " GAME OVER YOU LOST %i TO %i"

/**clears tinygl and sets text mode to scroll**/
static void display_set_scroll(void) //
{
    tinygl_clear();
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/** updates tinygl with #defined game title**/
void display_title(void)
{
    display_set_scroll();
    tinygl_text(TITLE_SCREEN_STRING);
}

/** updates tinygl with #defined gamemode string**/
void display_mode_three(void)
{
    display_set_scroll();
    tinygl_text(MODE_THREE_STRING);
}

/** updates tinygl with #defined gamemode string**/
void display_mode_five(void)
{
    display_set_scroll();
    tinygl_text(MODE_FIVE_STRING);
}

/** updates tinygl with #defined gamemode string**/
void display_mode_seven(void)
{
    display_set_scroll();
    tinygl_text(MODE_SEVEN_STRING);
}

/** updates tinygl with #defined round win string**/
void display_round_win(void)
{
    display_set_scroll();
    tinygl_text(ROUND_WIN_STRING);
}

/** updates tinygl with #defined round lose string**/
void display_round_lose(void)
{
    display_set_scroll();
    tinygl_text(ROUND_LOSE_STRING);
}

/** updates tinygl with #defined round tie string**/
void display_round_tie(void)
{
    display_set_scroll();
    tinygl_text(TIE_STRING);
}

/** updates tinygl with formatted score string**/
void display_score(int local, int remote)
{
    char score_str[sizeof(SCORE_STRING)];
    sprintf(score_str, SCORE_STRING, local, remote); //formats string to buffer
    display_set_scroll();
    tinygl_text(score_str);
}

/** updates tinygl with formatted game win string**/
void display_game_win(int local, int remote)
{
    char end_str[sizeof(GAME_WIN_STRING)];
    sprintf(end_str, GAME_WIN_STRING, local, remote); //formats string to buffer
    display_set_scroll();
    tinygl_text(end_str);
}

/** updates tinygl with formatted game lose string**/
void display_game_lose(int local, int remote)
{
    char end_str[sizeof(GAME_LOSE_STRING)];
    sprintf(end_str, GAME_LOSE_STRING, local, remote); //formats string to buffer
    display_set_scroll();
    tinygl_text(end_str);
}

/** updates tinygl with formatted text buffer to display character**/
void display_character (char character)
{
    char buffer[2]; //as only a single character is provided
    buffer[0] = character; //a two character array is initialised to hold
    buffer[1] = '\0'; //the displayed character and a terminator character
    tinygl_text (buffer);
}

