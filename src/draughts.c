/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"

void print_welcome(){
  printf("English Draughts – Main Menu\n");
  printf("1) Play Game\n");
  printf("2) Display Winners\n");
  printf("3) Reset scoreboard\n");
  printf("4) Quit\n");
}

int main (int argc, char *argv[])
{
  struct result scoreboard[SCOREBOARDSIZE];
  int user_selection;
  BOOLEAN is_end = FALSE;
  char player_one[MAX_NAME_LEN+1];
  char player_two[MAX_NAME_LEN+1];
  struct result game_result[SCOREBOARDSIZE];
  struct result last_result;
  char is_play_again = 'n';

  init_scoreboard(game_result);

  do{
    print_welcome();
    scanf("%d", &user_selection);
    read_rest_of_line();

    switch (user_selection) {
    case 1:
      memset(player_one, '\0', MAX_NAME_LEN+1);
      memset(player_two, '\0', MAX_NAME_LEN+1);

      printf("please enter the name of player one: \n");
      scanf("%s",player_one);
      read_rest_of_line();

      printf("please enter the name of player two: \n");
      scanf("%s",player_two);
      read_rest_of_line();

      do{
        play_game(player_one,player_two, &last_result);
        add_to_scoreboard(game_result, &last_result);
        printf("do you want play again with same player.y or n :");
        is_play_again = getchar();
        if(! is_play_again == 'y'){
          break;
        }
      } while (TRUE);
      break;
    case 2:
      display_scoreboard(game_result);
      break;
    case 3:
      reset_scoreboard(game_result);
      break;
    case 4:
      is_end = TRUE;
      break;
    default:
      ;
    }

    if(is_end){
      break;
    }
  } while (TRUE);

  return EXIT_SUCCESS;
}
