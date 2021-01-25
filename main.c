#include "board.h"

int main(int argc, char *argv[])
{
    char *board;
    int board_x, board_y;

    if (argc != 3)
    {
        fprintf(stderr, "Invalid arguments supplied should be BOARD_SIZE_X BOARD_SIZE_Y\n"
                        "(e.g. 30 15)");
        return -1;
    }

    board_x = atoi(argv[1]);
    board_y = atoi(argv[2]);
    board = (char *)malloc(sizeof(char) * board_x * board_y);

    memset(board, '.', sizeof(char) * board_x * board_y);

    begin_simulation(board, board_x, board_y);

    return 0;
}