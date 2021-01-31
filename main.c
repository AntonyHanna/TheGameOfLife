#include "board.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Invalid arguments supplied should be BOARD_SIZE_X BOARD_SIZE_Y\n"
                        "(e.g. 30 15)");
        return -1;
    }

    board_info *info = malloc(sizeof(board_info));

    info->len_x = atoi(argv[1]);
    info->len_y = atoi(argv[2]);
    info->board = (char *)malloc(sizeof(char) * info->len_x * info->len_y);

    memset(info->board, '.', sizeof(char) * info->len_x * info->len_y);
    begin_simulation(*info);

    free(info->board);
    free(info);
    
    return 0;
}