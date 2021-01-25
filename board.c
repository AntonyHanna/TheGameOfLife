#include "board.h"

// might segfault with dynamicly sized arrays
void print_board(char *board, size_t len_x, size_t len_y)
{
    for (uint8_t y = 0; y < len_y; y++)
    {
        for (uint8_t x = 0; x < len_x; x++)
        {
            printf("%c ", get_char_at_point(board, len_x, len_y, x, y));
        }

        printf("\n");
    }
}

void populate_live_cells(char *board, size_t len_x, size_t len_y)
{
    srand(time(NULL));

    for (uint8_t y = 0; y < len_y; y++)
    {
        for (uint8_t x = 0; x < len_x; x++)
        {
            // 50 percent chance of spawning
            if (rand() % 2 == 0)
            {
                set_cell_to_char(board, len_x, len_y, x, y, '+');
            }
        }
    }
}

void update_board_state(char *board, size_t len_x, size_t len_y)
{
    char *boardCopy;

    boardCopy = malloc(sizeof(char) * len_x * len_y);

    memcpy(boardCopy, board, sizeof(char) * len_x * len_y);

    for (uint8_t y = 0; y < len_y; y++)
    {
        for (uint8_t x = 0; x < len_x; x++)
        {
            uint8_t count = count_live_neigbours(board, len_x, len_y, x, y);

            if (get_char_at_point(board, len_x, len_y, x, y) == '+')
            {
                // same as if count == 2 || count == 3
                if (count <= 1 || count >= 4)
                {
                    set_cell_to_char(boardCopy, len_x, len_y, x, y, '.');
                }
            }

            else if (get_char_at_point(board, len_x, len_y, x, y) == '.')
            {
                if (count == 3)
                {
                    set_cell_to_char(boardCopy, len_x, len_y, x, y, '+');
                }
            }
        }
    }

    memcpy(board, boardCopy, sizeof(char) * len_x * len_y);
    free(boardCopy);
}

uint8_t validate_point(size_t len_x, size_t len_y, int8_t x, int8_t y)
{
    if (x < 0 || x > len_x ||
        y < 0 || y > len_y)
    {
        return 0;
    }

    return 1;
}

char get_char_at_point(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y)
{
    if (validate_point(len_x, len_y, x, y))
    {
        return board[get_index(len_y, x, y)];
    }

    return -1;
}

uint8_t count_live_neigbours(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y)
{
    uint8_t ret = 0;
    // left and right
    if (get_char_at_point(board, len_x, len_y, x + 1, y) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, len_x, len_y, x - 1, y) == '+')
    {
        ret++;
    }

    // top and bottom
    if (get_char_at_point(board, len_x, len_y, x, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, len_x, len_y, x, y - 1) == '+')
    {
        ret++;
    }

    // top right and bottom left corners
    if (get_char_at_point(board, len_x, len_y, x + 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, len_x, len_y, x - 1, y - 1) == '+')
    {
        ret++;
    }

    // top left and bottom right corners
    if (get_char_at_point(board, len_x, len_y, x - 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(board, len_x, len_y, x + 1, y - 1) == '+')
    {
        ret++;
    }

    return ret;
}

uint8_t set_cell_to_char(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y, char fill)
{
    if (validate_point(len_x, len_y, x, y))
    {
        board[get_index(len_y, x, y)] = fill;
        return 1;
    }
    return 0;
}

void begin_simulation(char *board, size_t len_x, size_t len_y)
{
    populate_live_cells(board, len_x, len_y);
    print_board(board, len_x, len_y);
    printf("\n")

    while (1)
    {
        update_board_state(board, len_x, len_y);
        print_board(board, len_x, len_y);
        printf("\n");
        sleep(1);
    }
}

uint16_t get_index(size_t len_y, int8_t x, int8_t y)
{
    return (len_y * x) + y;
}