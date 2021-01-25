#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
Structs
I just needed a header for this one :(
*/
typedef struct board_info
{
	char *board;
	size_t len_x;
	size_t len_y;
} board_info;

/* 
MUTATION FUNCTIONS 
Will modify the board passed to it
*/
uint8_t set_cell_to_char(board_info info, int8_t x, int8_t y, char fill);
void update_board_state(board_info info);
void begin_simulation(board_info info);
void populate_live_cells(board_info info);

/* 
GETTERS
Help in grabbing data from the board
*/
char get_char_at_point(board_info info, int8_t x, int8_t y);
uint16_t get_index(size_t len_y, int8_t x, int8_t y); /* takes a 2d index and returns a 1d index */

/*
HELPERS
These are just useful functions that i don't know how to categorize :)
*/
uint8_t validate_point(board_info info, int8_t x, int8_t y);
uint8_t count_live_neigbours(board_info info, int8_t x, int8_t y);
void print_board(board_info info);