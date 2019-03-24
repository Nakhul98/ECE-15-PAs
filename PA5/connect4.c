#include <stdio.h>
#include <stdlib.h>
#include "connect4.h"
#include "display_board.h"

// Start the simulation
int main() {	

	int board[BOARD_SIZE_HORZ][BOARD_SIZE_VERT] = {0};

	// Seed the random number generator
	srand(time(NULL));


	// Inform the user
	printf("\n Program has started ... \n");
	printf(" Launching game board window now ... \n");
	printf(" This may take some time if you are doing this remotely ... \n");

  	
	// To display the game board, you can use one of these
	// functions. 
	display_board(board);
	display_board_ASCII(board);


	// Wait for a user input 
	char symbol;
	do {
	    printf("Do you want to continue (y/n)? ");
	    scanf(" %c",&symbol);
	} while (symbol!='y'); 
	printf("\n");


	// Close the graphics window (important: do not forget this)
	close_board();

}

