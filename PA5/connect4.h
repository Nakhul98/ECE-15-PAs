#define BOARD_SIZE_VERT		6
#define BOARD_SIZE_HORZ		7


// Supporting functions for connect four
int valid_move(int board[][BOARD_SIZE_VERT], int move);
int check_winning(int board[][BOARD_SIZE_VERT], int last_move);
int player_move(int board[][BOARD_SIZE_VERT]);
int computer_move(int board[][BOARD_SIZE_VERT], int player, int mode);
int add_move_board(int board[][BOARD_SIZE_VERT], int move, int player);


