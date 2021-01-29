#include "board.h"

// might segfault with dynamicly sized arrays
void print_board(board_info info)
{
    for (uint8_t y = 0; y < info.len_y; y++)
    {
        for (uint8_t x = 0; x < info.len_x; x++)
        {
            printf("%c ", get_char_at_point(info, x, y));
        }

        printf("\n");
    }
}

void populate_live_cells(board_info info)
{
    srand(time(NULL));

    for (uint8_t y = 0; y < info.len_y; y++)
    {
        for (uint8_t x = 0; x < info.len_x; x++)
        {
            // 50 percent chance of spawning
            if (rand() % 2 == 0)
            {
                set_cell_to_char(info, x, y, '+');
            }
        }
    }
}

void update_board_state(board_info info)
{
    board_info *tmp_info;

    // fill in the tmp board_info
    tmp_info = malloc(sizeof(board_info));
    tmp_info->len_x = info.len_x;
    tmp_info->len_y = info.len_y;
    tmp_info->board = (char *)malloc(sizeof(char) * tmp_info->len_x * tmp_info->len_y);

    memcpy(tmp_info->board, info.board, sizeof(char) * info.len_x * info.len_y);

    for (uint8_t y = 0; y < info.len_y; y++)
    {
        for (uint8_t x = 0; x < info.len_x; x++)
        {
            uint8_t count = count_live_neigbours(info, x, y);

            if (get_char_at_point(info, x, y) == '+')
            {
                if (count != 2 && count != 3)
                {
                    set_cell_to_char(*tmp_info, x, y, '.');
                }
            }

            else if (get_char_at_point(info, x, y) == '.')
            {
                if (count == 3)
                {
                    set_cell_to_char(*tmp_info, x, y, '+');
                }
            }
        }
    }

    memcpy(info.board, tmp_info->board, sizeof(char) * info.len_x * info.len_y);

    free(tmp_info->board);
    free(tmp_info);
}

uint8_t validate_point(board_info info, int8_t x, int8_t y)
{
    if (x < 0 || x >= info.len_x ||
        y < 0 || y >= info.len_y)
    {
        return 0;
    }

    return 1;
}

char get_char_at_point(board_info info, int8_t x, int8_t y)
{
    if (validate_point(info, x, y))
    {
        return info.board[get_index(info.len_y, x, y)];
    }

    return -1;
}

uint8_t count_live_neigbours(board_info info, int8_t x, int8_t y)
{
    uint8_t ret = 0;
    // left and right
    if (get_char_at_point(info, x + 1, y) == '+')
    {
        ret++;
    }
    if (get_char_at_point(info, x - 1, y) == '+')
    {
        ret++;
    }

    // top and bottom
    if (get_char_at_point(info, x, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(info, x, y - 1) == '+')
    {
        ret++;
    }

    // top right and bottom left corners
    if (get_char_at_point(info, x + 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(info, x - 1, y - 1) == '+')
    {
        ret++;
    }

    // top left and bottom right corners
    if (get_char_at_point(info, x - 1, y + 1) == '+')
    {
        ret++;
    }
    if (get_char_at_point(info, x + 1, y - 1) == '+')
    {
        ret++;
    }

    return ret;
}

uint8_t set_cell_to_char(board_info info, int8_t x, int8_t y, char fill)
{
    if (validate_point(info, x, y))
    {
        info.board[get_index(info.len_y, x, y)] = fill;
        return 1;
    }
    return 0;
}

void begin_simulation(board_info info)
{
    populate_live_cells(info);
    print_board(info);
    printf("\n");

    while (1)
    {
        update_board_state(info);
        print_board(info);
        printf("\n");
        sleep(1);
    }
}

uint16_t get_index(size_t len_y, int8_t x, int8_t y)
{
    return (len_y * x) + y;
}