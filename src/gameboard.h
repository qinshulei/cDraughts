/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "utility.h"

#define BOARDWIDTH 8
#define BOARDHEIGHT  BOARDWIDTH
#define WHITE_DISPLAY "\x1b[39m" "o"
#define WHITE_KING_DISPLAY "\x1b[39m" "O"
#define RED_DISPLAY "\x1b[31m" "o"
#define RED_KING_DISPLAY "\x1b[31m" "O"
#define WHITE_RESET "\x1b[39m"


enum cell_contents
{
    EMPTY, RED, WHITE, K_RED, K_WHITE
};

/* Global variable - this is an example of the occasional exemption to
 * the rule against global variables. Be aware that this should be the
 * only global variable in your program */
static const enum cell_contents master_board[BOARDWIDTH][BOARDHEIGHT] =
{
    {RED, EMPTY, RED, EMPTY, RED, EMPTY, RED, EMPTY},
    {EMPTY, RED, EMPTY, RED, EMPTY, RED, EMPTY, RED},
    {RED, EMPTY, RED, EMPTY, RED, EMPTY, RED, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE},
    {WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY},
    {EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE}
};

/* Requirement 3 - Copies the contents of the master_board to a local
 * board for each game */
void init_gameboard(enum cell_contents board[][BOARDWIDTH]);

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH]);


#endif
