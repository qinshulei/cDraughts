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

    if( test_for_winner( &white_player_struct, gameboard)){
      strcpy(outcome->won, red_player_struct.name);
      strcpy(outcome->lost, white_player_struct.name);
      break;
    }

    player_turn( &red_player_struct, gameboard);
    display_gameboard(gameboard);

    if( test_for_winner( &red_player_struct, gameboard)){
      strcpy(outcome->won, white_player_struct.name);
      strcpy(outcome->lost, red_player_struct.name);
      break;
    }
    player_turn( &white_player_struct, gameboard);
  }
}

/* Requirement 5 - Handles the logic for the player's turn*/
void player_turn(struct player * current,
                 enum cell_contents board[][BOARDWIDTH])
{
  enum cell_contents temp_cell;
  char is_attack = 'n';
  struct move current_move;
  struct move attack_move;
  enum move_type current_move_type;

  do {
    printf("It is %s's turn. the color is %s.Please enter a move [press enter or ctrl-D to quit the current game]:",current->name, current->col == P_RED ? "red" : "white");
    scanf("%o,%o-%o,%o", &current_move.start.x, &current_move.start.y,&current_move.end.x,&current_move.end.y);
    read_rest_of_line();
    current_move_type = is_valid_move( current_move, current, board);
    if(current_move_type == INVALID){
      printf("Your move is (%d,%d) (%d,%d) ", current_move.start.x,current_move.start.y,current_move.end.x,current_move.end.y);
      printf("Your move is invalid,please try again\n");
    } else {
      break;
    }

  } while ( TRUE );

  switch ( current_move_type ) {
  case NORMAL:
    temp_cell = board[current_move.start.y][current_move.start.x];
    board[current_move.start.y][current_move.start.x] = EMPTY;

    if(current->col == P_RED && current_move.end.y == 7){
      board[current_move.end.y][current_move.end.x] = K_RED;
    } else if(current->col == P_WHITE && current_move.end.y == 0){
      board[current_move.end.y][current_move.end.x] = K_WHITE;
    }else {
      board[current_move.end.y][current_move.end.x] = temp_cell;
    }

    break;
  case ATTACK:
    temp_cell = board[current_move.start.y][current_move.start.x];
    board[current_move.start.y][current_move.start.x] = EMPTY;
    board[(current_move.start.y + current_move.end.y) / 2][(current_move.start.x + current_move.end.x) / 2] = EMPTY;

    if(current->col == P_RED && current_move.end.y == 7){
      board[current_move.end.y][current_move.end.x] = K_RED;
    } else if(current->col == P_WHITE && current_move.end.y == 0){
      board[current_move.end.y][current_move.end.x] = K_WHITE;
    }else {
      board[current_move.end.y][current_move.end.x] = temp_cell;
    }


    do{
      printf("You attacked! Would you like to attempt a further attack move with this token? [y for yes, n for no or press enter or ctrl-D to quit the current game]:");
      is_attack = getchar();
      read_rest_of_line();
      if(is_attack == 'y'){

        do {
          printf("It is %s's turn. Please enter a move [press enter or ctrl-D to quit the current game]:",current->name);
          scanf("%o,%o-%o,%o", &attack_move.start.x, &attack_move.start.y,&attack_move.end.x,&attack_move.end.y);

          read_rest_of_line();
          current_move_type = is_valid_move( current_move, current, board);
          if(current_move_type != ATTACK){
            printf("Your move is not a attack move,please try again\n");
          } else {
            break;
          }

        } while ( TRUE );

        temp_cell = board[attack_move.start.y][attack_move.start.x];
        board[attack_move.start.y][attack_move.start.x] = EMPTY;
        board[(attack_move.start.y + attack_move.end.y) / 2][(attack_move.start.x + attack_move.end.x) / 2] = EMPTY;

        if(current->col == P_RED && attack_move.end.y == 7){
          board[attack_move.end.y][attack_move.end.x] = K_RED;
        } else if(current->col == P_WHITE && attack_move.end.y == 0){
          board[attack_move.end.y][attack_move.end.x] = K_WHITE;
        }else {
          board[attack_move.end.y][attack_move.end.x] = temp_cell;
        }

      }else if(is_attack == 'n'){
        break;
      } else {
        break;
      }
    } while (TRUE);
    break;
  default:
    ;
  }


}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move,
                             struct player * current, enum cell_contents board[][BOARDWIDTH])
{
  // normal move
  if( next_move.start.x>=0 && next_move.start.y>=0 && next_move.end.x>=0 && next_move.end.y>=0 && next_move.start.x<=7 && next_move.start.y<=7 && next_move.end.x<=7 && next_move.end.y<=7){
    if( (board[next_move.start.y][next_move.start.x]==RED && current->col==P_RED && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==1 && next_move.end.y-next_move.start.y==1)
        ||  (board[next_move.start.y][next_move.start.x]==WHITE && current->col==P_WHITE && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==1 && next_move.start.y-next_move.end.y==1)
        ||  (board[next_move.start.y][next_move.start.x]==K_WHITE && current->col==P_WHITE && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==1 && abs(next_move.start.y-next_move.end.y)==1)
        ||  (board[next_move.start.y][next_move.start.x]==K_RED && current->col==P_RED && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==1 && next_move.end.y-next_move.start.y==1) ){
      return NORMAL;
    } else if( (board[next_move.start.y][next_move.start.x]==RED && current->col==P_RED && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==2 && next_move.end.y-next_move.start.y==2)
               ||  (board[next_move.start.y][next_move.start.x]==WHITE && current->col==P_WHITE && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==2 && next_move.start.y-next_move.end.y==2)
               ||  (board[next_move.start.y][next_move.start.x]==K_WHITE && current->col==P_WHITE && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==1 && abs(next_move.start.y-next_move.end.y)==2)
               ||  (board[next_move.start.y][next_move.start.x]==K_RED && current->col==P_RED && board[next_move.end.y][next_move.end.x]==EMPTY && abs(next_move.end.x-next_move.start.x)==2 && next_move.end.y-next_move.start.y==2) ){
      return ATTACK;
    }
  }

  return INVALID;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player,
                        enum cell_contents board[][BOARDWIDTH])
{
  int i,j;
  struct move possible_move_left,possible_move_right;
  struct move possible_king_move_left,possible_king_move_right;
  BOOLEAN has_moves = TRUE;

  for( i = 0; i <  BOARDHEIGHT; i++ ){
    for (j = 0; j < BOARDWIDTH; j++) {
      if(board[i][j] == RED && next_player->col == P_RED){
        possible_move_left.start.x = j;
        possible_move_left.start.y = i;
        possible_move_left.end.x = j - 1;
        possible_move_left.end.y = i + 1;
        if( !(is_valid_move(possible_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_move_right.start.x = j;
        possible_move_right.start.y = i;
        possible_move_right.end.x = j + 1;
        possible_move_right.end.y = i + 1;
        if( !(is_valid_move(possible_move_right,next_player,board) == INVALID)){
          return FALSE;
        }

      }else if(board[i][j] == K_RED && next_player->col == P_RED){
        possible_move_left.start.x = j;
        possible_move_left.start.y = i;
        possible_move_left.end.x = j - 1;
        possible_move_left.end.y = i + 1;
        if( !(is_valid_move(possible_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_move_right.start.x = j;
        possible_move_right.start.y = i;
        possible_move_right.end.x = j + 1;
        possible_move_right.end.y = i + 1;
        if( !(is_valid_move(possible_move_right,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_king_move_left.start.x = j;
        possible_king_move_left.start.y = i;
        possible_king_move_left.end.x = j - 1;
        possible_king_move_left.end.y = i - 1;
        if( !(is_valid_move(possible_king_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_king_move_right.start.x = j;
        possible_king_move_right.start.y = i;
        possible_king_move_right.end.x = j + 1;
        possible_king_move_right.end.y = i - 1;
        if( !(is_valid_move(possible_king_move_right,next_player,board) == INVALID)){
          return FALSE;
        }

      } else if(board[i][j] == WHITE && next_player->col == P_WHITE){
        possible_move_left.start.x = j;
        possible_move_left.start.y = i;
        possible_move_left.end.x = j - 1;
        possible_move_left.end.y = i - 1;
        if( !(is_valid_move(possible_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_move_right.start.x = j;
        possible_move_right.start.y = i;
        possible_move_right.end.x = j + 1;
        possible_move_right.end.y = i - 1;
        if( !(is_valid_move(possible_move_right,next_player,board) == INVALID)){
          return FALSE;
        }

      } else if(board[i][j] == K_WHITE && next_player->col == P_WHITE){
        possible_move_left.start.x = j;
        possible_move_left.start.y = i;
        possible_move_left.end.x = j - 1;
        possible_move_left.end.y = i - 1;
        if( !(is_valid_move(possible_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_move_right.start.x = j;
        possible_move_right.start.y = i;
        possible_move_right.end.x = j + 1;
        possible_move_right.end.y = i - 1;
        if( !(is_valid_move(possible_move_right,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_king_move_left.start.x = j;
        possible_king_move_left.start.y = i;
        possible_king_move_left.end.x = j - 1;
        possible_king_move_left.end.y = i + 1;
        if( !(is_valid_move(possible_king_move_left,next_player,board) == INVALID)){
          return FALSE;
        }

        possible_king_move_right.start.x = j;
        possible_king_move_right.start.y = i;
        possible_king_move_right.end.x = j + 1;
        possible_king_move_right.end.y = i + 1;
        if( !(is_valid_move(possible_king_move_right,next_player,board) == INVALID)){
          return FALSE;
        }
      }
    }
  }

  return has_moves;
}
