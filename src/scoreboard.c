/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"

/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
  memset(scoreboard, '\0', 10*2*(MAX_NAME_LEN+1));
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, 
    struct result * latest_game)
{
  int i;
  for( i = SCOREBOARDSIZE - 1 ; i > 0 ; i--){
    memcpy((scoreboard + i),(scoreboard + i - 1),sizeof(struct result));
  }
  memcpy(scoreboard,latest_game,sizeof(struct result));
}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
  memset(scoreboard, '\0', 10*2*(MAX_NAME_LEN+1));
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
  int i;

  printf("APT English Draughts Tournament - History of Games Played.\n");
  printf("==========================================================\n");
  printf("| Winner                     | Loser                     |\n");
  printf("| -------------------------- | ------------------------- |\n");
  for( i=0; i < SCOREBOARDSIZE; i++){
    if(! strcmp((scoreboard + i)->won,"")){
      printf("| %s | %s |\n",(scoreboard + i)->won,(scoreboard + i)->lost);
    }
  }
}

