#include "board.h"

int main(int argc, char *argv[])
{
    char board[BOARD_SIZE_X][BOARD_SIZE_Y];
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int y = 0; y < BOARD_SIZE_Y; y++)
        {
            board[i][y] = '.';
        }
    }

    print_board(board);
    printf("\n\n");
    populate_live_cells(board);
    printf("\n\n");
    print_board(board);

    begin_simulation(board);

    return 0;
}