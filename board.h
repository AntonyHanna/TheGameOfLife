#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 
MUTATION FUNCTIONS 
Will modify the board passed to it
*/
uint8_t set_cell_to_char(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y, char fill);
void update_board_state(char *board, size_t len_x, size_t len_y);
void begin_simulation(char *board, size_t len_x, size_t len_y);
void populate_live_cells(char *board, size_t len_x, size_t len_y);

/* 
GETTERS
Help in grabbing data from the board
*/
char get_char_at_point(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y);
uint16_t get_index(size_t len_y, int8_t x, int8_t y); /* takes a 2d index and returns a 1d index */

/*
HELPERS
These are just useful functions that i don't know how to categorize :)
*/
uint8_t validate_point(size_t len_x, size_t len_y, int8_t x, int8_t y);
uint8_t count_live_neigbours(char *board, size_t len_x, size_t len_y, int8_t x, int8_t y);
void print_board(char *board, size_t len_x, size_t len_y);