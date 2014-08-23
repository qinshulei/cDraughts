/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"

/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two,
               struct result * outcome)
{
  BOOLEAN is_quit = FALSE;
  BOOLEAN is_end_game = FALSE;
  enum cell_contents gameboard[BOARDWIDTH][BOARDHEIGHT];
  int random = rand() % 2;
  struct player red_player_struct;
  struct player white_player_struct;
  red_player_struct.col = P_RED;
  white_player_struct.col = P_WHITE;

  if (random){
    strcpy(red_player_struct.name, player_one);
    strcpy(white_player_struct.name, player_two);
  }else{
    strcpy(red_player_struct.name, player_two);
    strcpy(white_player_struct.name, player_one);
  }

  init_gameboard(gameboard);
  
  while( !is_quit && !is_end_game ){
    display_gameboard(gameboard);

    if( !test_for_winner( &white_player_struct, gameboard)){
      break;
    }

    player_turn( &red_player_struct, gameboard);
    display_gameboard(gameboard);

    if( !test_for_winner( &red_player_struct, gameboard)){
      break;
    }
    player_turn( &white_player_struct, gameboard);
  }


  display_gameboard(gameboard);
  printf("user1 : %s , user2 : %s \n", player_one, player_two);
}

/* Requirement 5 - Handles the logic for the player's turn*/
void player_turn(struct player * current,
                 enum cell_contents board[][BOARDWIDTH])
{
  enum cell_contents temp_cell;
  char is_attack = 'n';
  struct move current_move;
  printf("%s player's turn\n", current->name);
  printf("It is %s's turn. Please enter a move [press enter or ctrl-D to quit the current game]:",current->name);
  scanf("%o,%o-%o,%o", &current_move.start.x, &current_move.start.y,&current_move.end.x,&current_move.end.y);
  read_rest_of_line();

  switch (is_valid_move( current_move, current, board)) {
  case NORMAL:
    temp_cell = board[current_move.start.y][current_move.start.x];
    board[current_move.start.y][current_move.start.x] = EMPTY;
    board[current_move.end.y][current_move.end.x] = temp_cell;
    break;
  case ATTACK:
    printf("You attacked! Would you like to attempt a further attack move with this token? [y for yes, n for no or press enter or ctrl-D to quit the current game]:");
    is_attack = getchar();
    read_rest_of_line();
    if(is_attack == 'y'){
      
    }else if(is_attack == 'n'){

    } else {

    }

    break;
  case INVALID:
    break;
  default:
    ;
  }


}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
                             struct player * current, enum cell_contents board[][BOARDWIDTH])
{
  /* Delete this comment and write your own comments and code here*/

  return INVALID;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
                        enum cell_contents board[][BOARDWIDTH])
{
  printf("%s player has move way\n", next_player->name);
  BOOLEAN has_moves = TRUE;

  //TODO temp set FALSE
  static int i = 0;
  if(i > 5){
    has_moves = FALSE;
  }
  i++;

  return has_moves;
}
