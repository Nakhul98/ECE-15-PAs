#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"

// Checks whether 'move' is valid given the current state of 'board'.
// It returns 1 when the move is valid, otherwise 0.
int valid_move(int board[][BOARD_SIZE_VERT], int move) {
	// Complete this function
  int i;
  // checks if the move is within bounds of array
  if((move >= 0) && (move <= BOARD_SIZE_HORZ - 1)) {
    /* check if the first row of the acccessed column is free - if so, then returns 1 */
    if(board[move][BOARD_SIZE_VERT - 1] == 0) {
      return 1;
    }

  }

  // returns 0 if move invalid
  return 0;
}


// Checks whether there is a winning player on the board.
// It gets passed the last move that was made.
// It returns 0 if there is no winner, or the otherwise the number
// of the player who won (1 or 2).
int check_winning(int board[][BOARD_SIZE_VERT], int last_move) {
	// Complete this function
  int i, j, count;

  // checks if a horizontal win
  // loop accesses the vertical
  for(i = 0; i < BOARD_SIZE_VERT - 1; i++) {
    count = 0;
    // loop accesses the horizontal
    for(j = 0; j < BOARD_SIZE_HORZ - 1; j++) {
      if(j == 0) {
	continue;
      }
      if(board[j][i] == board[j-1][i]) {
	count++;
      }
      if(count == 4) {
	if(board[j][i] == 1) {
	  return 1;
	}
	if(board[j][i] == 1) {
          return 2;
	}
      }
    }
  }

  count = 0;
  //checks if a vertical is winning
  for(i = 0; i < BOARD_SIZE_VERT; i++) {
    if(i == 0) {
      continue;
    }
    if(board[last_move][i] == board[last_move][i-1]) {
      count++;
    }
    if(count == 4) {
      if(board[last_move][i] == 2) {
	return 2;
      }
      if(board[last_move][i] == 1) {
	return 1;
      } 
    }
  }
}

// It asks the user to pick a column to play, and repeats
// this until a valid one is chosen.
// The user should enter a number between 1 and 7 (1-indexed).
// It returns the column in the board array, so a value between 
// 0 and 6 (BOARD_SIZE_HORZ-1) (0-indexed)
int player_move(int board[][BOARD_SIZE_VERT]) {
	// Complete this function
}


// This functions chooses a move for the computer player,
// given the state of the board and the player number the
// computer is playing with.
// It supports two modes: 0 when making random valid moves
// and 1 when using a more advanced algorithm.
// It returns the move chosen.
int computer_move(int board[][BOARD_SIZE_VERT], int player, int mode) {
	// Complete this function
  int move;
  #include <time.h>
  srand(time(0));
  
  // loops until a valid move is created
  while(valid_move(board, move = rand()) == 0);
  return move;
}	


// Update the board with a move for a specific player.
// Returns 0 in case of failure (the move is not a valid
// one); otherwise it returns 1. 
int add_move_board(int board[][BOARD_SIZE_VERT], int move, int player) {
	// Complete this function
  int i;

  // returns 0 if the board move is not valid
  if(valid_move(board, move) == 0) {
    return 0;
  }

  // accesses the bottom free row of the selected column
  for(i = 0; i < BOARD_SIZE_VERT - 1; i++) {
    if(board[move][i] != 0) {
      if(player == 1) {
	board[move][i-1] = 1;
	break;
      }
      else{
	board[move][i-1] = 2;
	break;
      }
    } 

  }
  return 1;
}
