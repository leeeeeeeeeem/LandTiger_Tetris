#include "field.h"
#include "GLCD.h"

#define FIELD_H 20
#define FIELD_W 10

#define BLOCK_SIZE 15

#define FIELD_PADDING 10

#define FIELD_TOP_LEFT_X FIELD_PADDING
#define FIELD_TOP_LEFT_Y FIELD_PADDING
#define FIELD_TOP_RIGHT_X FIELD_PADDING + BLOCK_SIZE * FIELD_W
#define FIELD_TOP_RIGHT_Y FIELD_PADDING
#define FIELD_BOTTOM_LEFT_X FIELD_PADDING
#define FIELD_BOTTOM_LEFT_Y FIELD_PADDING + BLOCK_SIZE * FIELD_H
#define FIELD_BOTTOM_RIGHT_X FIELD_PADDING + BLOCK_SIZE * FIELD_W
#define FIELD_BOTTOM_RIGHT_Y FIELD_PADDING + BLOCK_SIZE * FIELD_H

#define N_TETROMINOES 7

typedef struct current_tetromino_s{
		uint8_t index;
		uint8_t rotation;
		uint8_t position_x;
		uint8_t position_y;
		uint8_t placed;
		uint16_t color;
	} current_tetromino_t;

current_tetromino_t current_tetromino;

static uint8_t tetrominoes[N_TETROMINOES][4][4][4] = {			
													// Static data structure containing all 7 tetrominoes with
													// all 4 rotations.
													
											{ 		// I-shaped 
												{
													{1, 1, 1, 1},
													{0, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 0, 0, 0}
												},
												{
													{1, 1, 1, 1},
													{0, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 0, 0, 0}
												}
											},	
											{ 		// O-shaped 
												{
													{1, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{1, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}
											},
											{ 		// T-shaped 
												{
													{1, 1, 1, 0},
													{0, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{0, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 1, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{0, 1, 0, 0},
													{1, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 0, 0, 0},
													{1, 1, 0, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0}
												}
											},
											{ 		// J-shaped 
												{
													{0, 1, 0, 0},
													{0, 1, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{0, 0, 1, 0},
													{1, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 1, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}
											},
											{ 		// L-shaped 
												{
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{1, 1, 1, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 0, 0},
													{0, 1, 0, 0},
													{0, 1, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{0, 0, 1, 0},
													{1, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}
											},
											{ 		// S-shaped 
												{
													{0, 1, 1, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{1, 0, 0, 0},
													{1, 1, 0, 0},
													{0, 1, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{0, 1, 1, 0},
													{1, 1, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 0, 0, 0},
													{1, 1, 0, 0},
													{0, 1, 0, 0},
													{0, 0, 0, 0}
												}
											},
											{ 		// Z-shaped 
												{
													{1, 1, 0, 0},
													{0, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												}, 
												{
													{0, 1, 0, 0},
													{1, 1, 0, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 0, 0},
													{0, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{0, 1, 0, 0},
													{1, 1, 0, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0}
												}
											}
										};

uint16_t field[FIELD_H][FIELD_W];

void field_setBlock(int x, int y, uint16_t color){
	field[y][x] = color;
}

void field_update(){
	int i, j;
	for (i = 0; i < FIELD_H; i++){
		for (j = 0; j < FIELD_W; j++){
			if (field[i][j] == 0xFFFF)
				set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * j,
						FIELD_TOP_LEFT_Y + BLOCK_SIZE * i,
						BLOCK_SIZE,
						0x0000);
			else if (field[i][j])
				set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * j,
						FIELD_TOP_LEFT_Y + BLOCK_SIZE * i,
						BLOCK_SIZE,
						field[i][j]);
		}
	} 
}

void field_init(){
	int x, y;
	LCD_DrawLine(FIELD_TOP_LEFT_X - 1, FIELD_TOP_LEFT_Y - 1, FIELD_TOP_RIGHT_X + 1, FIELD_TOP_RIGHT_Y - 1, Grey);
	LCD_DrawLine(FIELD_TOP_LEFT_X - 1, FIELD_TOP_LEFT_X - 1, FIELD_BOTTOM_LEFT_X - 1, FIELD_BOTTOM_LEFT_Y + 1, Grey);
	LCD_DrawLine(FIELD_BOTTOM_LEFT_X - 1, FIELD_BOTTOM_LEFT_Y + 1, FIELD_BOTTOM_RIGHT_X + 1 , FIELD_BOTTOM_RIGHT_Y + 1, Grey);
	LCD_DrawLine(FIELD_BOTTOM_RIGHT_X + 1, FIELD_BOTTOM_RIGHT_Y + 1, FIELD_TOP_RIGHT_X + 1, FIELD_TOP_RIGHT_Y - 1, Grey);
	for (y = 0; y < FIELD_H; y++){
		for (x = 0; x < FIELD_W; x++){
			field[y][x] = 0;
		}
	}
}

void field_placeTetromino(uint8_t x, uint8_t y, uint8_t idx, uint8_t rotation, uint16_t color){
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			if (tetrominoes[idx][rotation][i][j])
				field_setBlock(x + j, y + i, color);
		}
	}
	current_tetromino.index = idx;
	current_tetromino.position_x = x;
	current_tetromino.position_y = y;
	current_tetromino.rotation = rotation;
	current_tetromino.placed = 0;
	current_tetromino.color = color;
	field_update();
}

void field_deleteCurrentTetromino(){
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (tetrominoes[current_tetromino.index][current_tetromino.rotation][i][j]) {
				field_setBlock(current_tetromino.position_x + j, 
					current_tetromino.position_y + i, 
					0xFFFF);
			}
		}
	}
}

void field_dropCurrentTetromino(){
	field_deleteCurrentTetromino();
	current_tetromino.position_y++;
	field_placeTetromino(
		current_tetromino.position_x, 
		current_tetromino.position_y,
		current_tetromino.index,
		current_tetromino.rotation,
		current_tetromino.color);
}

void field_rotateCurrentTetromino(){
	field_deleteCurrentTetromino();
	current_tetromino.rotation = (current_tetromino.rotation + 1) % 4;
	field_placeTetromino(
			current_tetromino.position_x, 
			current_tetromino.position_y,
			current_tetromino.index,
			current_tetromino.rotation,
			current_tetromino.color);
}
