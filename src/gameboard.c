/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "gameboard.h"

/* Copies the master board to a local copy for each game */
void init_gameboard(enum cell_contents board[][BOARDWIDTH])
{
  int i,j;
  for(i = 0;i<BOARDHEIGHT;i++){
    for (j = 0; j < BOARDHEIGHT; j++ ) {
      board[i][j] = master_board[i][j];
    }
  }
}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH])
{
  int i,j;

  for(i = 0;i <= BOARDHEIGHT;i++){
    for (j = 0; j <= BOARDWIDTH; j++ ) {
      if(i == 0 && j == 0){
        printf("     |");
      } else if(i == 0){
        printf("  %d  |", j - 1);
      }else if(j == 0){
        printf("  %d  |", i - 1);
      }else {
        printf("  ");
        switch (board[i-1][j-1]) {
        case EMPTY:
          printf(" ");
          break;
        case RED:
          printf(RED_DISPLAY);
          break;
        case WHITE:
          printf(WHITE_DISPLAY);
          break;
        case K_RED:
          printf(RED_KING_DISPLAY);
          break;
        case K_WHITE:
          printf(WHITE_KING_DISPLAY);
          break;
        default:
          ;
        }
        printf(WHITE_RESET);
        printf("  |");
      }
    }
    printf("\n------------------------------------------------------\n");
  }

}
