#include "board.h"

// might segfault with dynamicly sized arrays
void print_board(char board[BOARD_SIZE_X][BOARD_SIZE_Y])
{
    for (uint8_t y = 0; y < BOARD_SIZE_Y; y++)
    {
        for (uint8_t x = 0; x < BOARD_SIZE_X; x++)
        {
            printf("%c ", board[x][y]);
        }

        printf("\n");
    }
}

void populate_live_cells(char board[BOARD_SIZE_X][BOARD_SIZE_Y])
{
    srand(time(NULL));

    for (uint8_t y = 0; y < BOARD_SIZE_Y; y++)
    {
        for (uint8_t x = 0; x < BOARD_SIZE_X; x++)
        {
            // 50 percent chance of spawning
            if (rand() % 2 == 0)
            {
                board[x][y] = '+';
            }
        }
    }
}

void update_board_state(char board[BOARD_SIZE_X][BOARD_SIZE_Y])
{
    for (uint8_t y = 0; y < BOARD_SIZE_Y; y++)
    {
        for (uint8_t x = 0; x < BOARD_SIZE_X; x++)
        {
            if (get_char_at_point(board, x, y) == '+')
            {
                uint8_t count = count_live_neigbours(board, x, y);

                if (count == 2 || count == 3)
                {
                    continue;
                }
                else
                {
                    set_cell_to_char(board, x, y, '.');
                }
            }

            if (get_char_at_point(board, x, y) == '.')
            {
                uint8_t count = count_live_neigbours(board, x, y);

                if (count == 3)
                {
                    set_cell_to_char(board, x, y, '+');
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

uint8_t validate_point(int8_t x, int8_t y)
{
    if (x < 0 || x > BOARD_SIZE_X ||
        y < 0 || y > BOARD_SIZE_Y)
    {
        return 0;
    }

    return 1;
}

char get_char_at_point(char board[BOARD_SIZE_X][BOARD_SIZE_Y], int8_t x, int8_t y)
{
    if (validate_point(x, y))
    {
        return board[x][y];
    }

    return -1;
}

uint8_t count_live_neigbours(char board[BOARD_SIZE_X][BOARD_SIZE_Y], int8_t x, int8_t y)
{
    uint8_t ret = 0;
    // left and right
    if (get_char_at_point(board, x + 1, y) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, x - 1, y) == '+')
    {
        ret++;
    }

    // top and bottom
    if (get_char_at_point(board, x, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, x, y - 1) == '+')
    {
        ret++;
    }

    // top right and bottom left corners
    if (get_char_at_point(board, x + 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, x - 1, y - 1) == '+')
    {
        ret++;
    }

    // top left and bottom right corners
    if (get_char_at_point(board, x - 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, x + 1, y - 1) == '+')
    {
        ret++;
    }

    return ret;
}

uint8_t set_cell_to_char(char board[BOARD_SIZE_X][BOARD_SIZE_Y], int8_t x, int8_t y, char fill)
{
    if (validate_point(x, y))
    {
        board[x][y] = fill;
        return 1;
    }
    return 0;
}

void begin_simulation(char board[BOARD_SIZE_X][BOARD_SIZE_Y])
{
    populate_live_cells(board);

    while (1)
    {
        update_board_state(board);
        print_board(board);
        printf("\n");
        sleep(1);
    }
}