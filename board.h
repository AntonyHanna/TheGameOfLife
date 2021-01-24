#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_SIZE_X 30
#define BOARD_SIZE_Y 15

void print_board(char board[BOARD_SIZE_X][BOARD_SIZE_Y]);
void populate_live_cells(char board[BOARD_SIZE_X][BOARD_SIZE_Y]);
void update_board_state(char board[BOARD_SIZE_X][BOARD_SIZE_Y]);
uint8_t validate_point(int8_t x, int8_t y);
char get_char_at_point(char board[BOARD_SIZE_X][BOARD_SIZE_Y], int8_t x, int8_t y);
uint8_t count_live_neigbours(char board[BOARD_SIZE_X][BOARD_SIZE_Y], int8_t x, int8_t y);
void begin_simulation(char board[BOARD_SIZE_X][BOARD_SIZE_Y]);
