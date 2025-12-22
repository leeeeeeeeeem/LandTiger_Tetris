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


static uint8_t tetrominoes[N_TETROMINOES][4][4][4] = {			// Static data structure containing all 7 tetrominoes with
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

uint16_t field[FIELD_W][FIELD_H];

void field_setBlock(int x, int y, uint16_t color){
	field[x][y] = color;
}

void field_update(){
	int i, j;
	for (i = 0; i < FIELD_W; i++){
		for (j = 0; j < FIELD_H; j++){
			if (field[i][j])
				set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * i + 1,
						FIELD_TOP_LEFT_Y + BLOCK_SIZE * j + 1,
						BLOCK_SIZE,
						field[i][j]);
		}
	} 
}

void field_init(){
	int x, y;
	LCD_DrawLine(FIELD_TOP_LEFT_X, FIELD_TOP_LEFT_Y, FIELD_TOP_RIGHT_X, FIELD_TOP_RIGHT_Y, Grey);
	LCD_DrawLine(FIELD_TOP_LEFT_X, FIELD_TOP_LEFT_X, FIELD_BOTTOM_LEFT_X, FIELD_BOTTOM_LEFT_Y, Grey);
	LCD_DrawLine(FIELD_BOTTOM_LEFT_X, FIELD_BOTTOM_LEFT_Y, FIELD_BOTTOM_RIGHT_X, FIELD_BOTTOM_RIGHT_Y, Grey);
	LCD_DrawLine(FIELD_BOTTOM_RIGHT_X, FIELD_BOTTOM_RIGHT_Y, FIELD_TOP_RIGHT_X, FIELD_TOP_RIGHT_Y, Grey);
	for (x = 0; x < FIELD_W; x++){
		for (y = 0; y < FIELD_H; y++){
			field[x][y] = 0;
		}
	}
}






