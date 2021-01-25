#include "board.h"

int main(int argc, char *argv[])
{
    char board[BOARD_SIZE_X][BOARD_SIZE_Y];
    memset(board, '.', sizeof(char) * BOARD_SIZE_X * BOARD_SIZE_Y);

    print_board(board);
    printf("\n\n");
    populate_live_cells(board);
    printf("\n\n");
    print_board(board);

    begin_simulation(board);

    return 0;
}