#include "field.h"
#include "GLCD.h"
#include <stdlib.h>

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
#define N_COLORS 7

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
													{1, 0, 0, 0},
													{1, 1, 1, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 0, 0},
													{1, 0, 0, 0},
													{1, 0, 0, 0},
													{0, 0, 0, 0}
												},
												{
													{1, 1, 1, 0},
													{0, 0, 1, 0},
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

uint16_t colors[N_COLORS] = {
    0x94EA,
    0xFB15,
    0xCB5F,
    0x8DBF,
    0xFD47,
    0xA761,
    0xFB94,
};

uint16_t field[FIELD_H][FIELD_W];

typedef struct {
    uint8_t x;
    uint8_t y;
} cell_t;

cell_t toPlace[FIELD_H * FIELD_W];
uint8_t toPlace_count = 0;

uint8_t game_started = 0;
uint8_t game_running = 0;
uint8_t soft_drop = 0;
uint8_t hard_drop = 0;
uint8_t move_left = 0;
uint8_t move_right = 0;
uint8_t rotate = 0;

uint8_t tickN = 0;

uint32_t seed;

void mark_toPlace(uint8_t x, uint8_t y) {
    if (toPlace_count < FIELD_H * FIELD_W) {
        toPlace[toPlace_count].x = x;
        toPlace[toPlace_count].y = y;
        toPlace_count++;
    }
}

void field_setBlock(int x, int y, uint16_t color){
	if (field[y][x] != color) {
    	field[y][x] = color;
    	mark_toPlace(x, y);
    }
}

void field_update(){
	uint8_t i, x, y;
	for (i = 0; i < toPlace_count; i++) {
		x = toPlace[i].x;
		y = toPlace[i].y;
		if (field[y][x] == 0xFFFF) {
			set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * x, FIELD_TOP_LEFT_Y + BLOCK_SIZE * y, BLOCK_SIZE, 0x0000);
			field[y][x] = 0x0000;
		} 
		else if (field[y][x]) {
			set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * x, FIELD_TOP_LEFT_Y + BLOCK_SIZE * y, BLOCK_SIZE, field[y][x]);
		}
	}
	toPlace_count = 0;
	field_collisionDetection();
}

void field_init(){
	uint8_t x, y;
	LCD_DrawLine(FIELD_TOP_LEFT_X - 1, FIELD_TOP_LEFT_Y - 1, FIELD_TOP_RIGHT_X, FIELD_TOP_RIGHT_Y - 1, Grey);
	LCD_DrawLine(FIELD_TOP_LEFT_X - 1, FIELD_TOP_LEFT_Y - 1, FIELD_BOTTOM_LEFT_X - 1, FIELD_BOTTOM_LEFT_Y, Grey);
	LCD_DrawLine(FIELD_BOTTOM_LEFT_X - 1, FIELD_BOTTOM_LEFT_Y, FIELD_BOTTOM_RIGHT_X, FIELD_BOTTOM_RIGHT_Y, Grey);
	LCD_DrawLine(FIELD_BOTTOM_RIGHT_X, FIELD_BOTTOM_RIGHT_Y, FIELD_TOP_RIGHT_X, FIELD_TOP_RIGHT_Y - 1, Grey);
	for (y = 0; y < FIELD_H; y++){
		for (x = 0; x < FIELD_W; x++){
			field[y][x] = 0;
		}
	}
}

void field_placeTetromino(uint8_t x, uint8_t y, uint8_t idx, uint8_t rotation, uint16_t color, uint8_t update){
	uint8_t i, j;
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
	if (update)
		field_update();
}

uint8_t generate_idx(){
	seed = seed * 1103515245u + 12345u;
	return (uint8_t)(((seed >> 16) * 7u) >> 16);
}

void field_placeRandomTetromino(){
	int idx = generate_idx();
	field_placeTetromino(4, 0, idx, 0, colors[idx], 1);
}

void field_deleteCurrentTetromino(){
	uint8_t i, j;
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
		current_tetromino.color,
		0);
}

void field_hardDropCurrentTetromino(){
    field_deleteCurrentTetromino();
    while (!current_tetromino.placed){
        current_tetromino.position_y++;
        field_collisionDetection();
    }
    field_placeTetromino(
        current_tetromino.position_x,
        current_tetromino.position_y,
        current_tetromino.index,
        current_tetromino.rotation,
        current_tetromino.color,
        0
    );
}

void field_rotateCurrentTetromino(){
	uint8_t y, x, current_x, current_y, can_place = 1;
	uint8_t new_rotation = (current_tetromino.rotation + 1) % 4;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (tetrominoes[current_tetromino.index][new_rotation][y][x] &&
					!tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x]) {
				current_x = current_tetromino.position_x + x;
				current_y = current_tetromino.position_y + y;
				if (current_x >= FIELD_W || current_y >= FIELD_H) {
					can_place = 0;
					break;
				}
				if (field[current_y][current_x] != 0 && 
				    field[current_y][current_x] != 0xFFFF) {
					can_place = 0;
					break;
				}
			}
		}
		if (!can_place)
			break;
	}
	if (can_place) {
		field_deleteCurrentTetromino();
		current_tetromino.rotation = new_rotation;
		field_placeTetromino(
			current_tetromino.position_x, 
			current_tetromino.position_y,
			current_tetromino.index,
			current_tetromino.rotation,
			current_tetromino.color,
			0);
	}
}


void field_moveCurrentTetrominoRight(){
	uint8_t y, x, can_place = 1;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x] &&
					(current_tetromino.position_x + x + 1 >= FIELD_W	|| 
						(((x != 3 && !tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x + 1]) 
						 || (x == 3) ) &&
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x + 1] != 0 &&
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x + 1] != 0xFFFF)
					)
				){
					can_place = 0;
					break;
				 }
		}
	}
	if (can_place){
		field_deleteCurrentTetromino();
		field_placeTetromino(
			current_tetromino.position_x + 1, 
			current_tetromino.position_y,
			current_tetromino.index,
			current_tetromino.rotation,
			current_tetromino.color,
			0);
	}
}
		
void field_moveCurrentTetrominoLeft(){	
	uint8_t y, x, can_place = 1;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x] &&
					(current_tetromino.position_x + x - 1 < 0	|| 
						(((x != 0 && !tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x -	1]) 
						 || (x == 0) ) &&
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x - 1] != 0 &&
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x - 1] != 0xFFFF)
					)
				){
					can_place = 0;
					break;
				 }
		}
	}
	if (can_place){
		field_deleteCurrentTetromino();
		field_placeTetromino(
			current_tetromino.position_x - 1, 
			current_tetromino.position_y,
			current_tetromino.index,
			current_tetromino.rotation,
			current_tetromino.color,
			0);
	}
}

void field_collisionDetection(){
	uint8_t y, x;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (tetrominoes[current_tetromino.index][current_tetromino.rotation][y][x] &&
				(y == 3 || !tetrominoes[current_tetromino.index][current_tetromino.rotation][y + 1][x]) &&
					(
					 current_tetromino.position_y + y >= FIELD_H - 1 ||
					 (field[current_tetromino.position_y + y + 1][current_tetromino.position_x + x] != 0 &&
					  field[current_tetromino.position_y + y + 1][current_tetromino.position_x + x] != 0xFFFF)
					)
				) 
						current_tetromino.placed = 1;
		}
	}
}

void field_clearDetection(){
    uint8_t y, x, cleared;
    for (y = 0; y < FIELD_H; y++){
        cleared = 1;
        for (x = 0; x < FIELD_W; x++){
            if (field[y][x] == 0 || field[y][x] == 0xFFFF)
                cleared = 0;
        }
        if (cleared)
            field_clearRow(y);
    }
}

void field_clearRow(uint8_t y_toClear){
    uint8_t y, x;
    for (y = y_toClear; y > 0; y--) {
        for (x = 0; x < FIELD_W; x++) {
            if (field[y - 1][x] == 0x0000)
                field_setBlock(x, y, 0xFFFF); 
						else
                field_setBlock(x, y, field[y - 1][x]);
        }
    }
    for (x = 0; x < FIELD_W; x++) {
        field_setBlock(x, 0, 0xFFFF);
    }
    field_update();
}


void request_hardDrop(){
	hard_drop = 1;
}

void request_moveRight(){
	move_right = 1;
}

void request_moveLeft(){
	move_left = 1;
}

void request_rotate(){
	rotate = 1;
}

void set_softDrop(void){
	soft_drop = 1;
}

void unset_softDrop(void){
	soft_drop = 0;
}

void toggle_running(void){
	game_running = !game_running;
	if (game_running && !game_started)
		start_game();
}

void start_game(){
	seed = LPC_TIM0->TC;
	game_started = 1;
	tickN = 0;
	field_placeRandomTetromino();
}

void advance_game(){
	if (!game_running)
		return;
	tickN++;	
	if (rotate)
		field_rotateCurrentTetromino();
	if (move_left)
		field_moveCurrentTetrominoLeft();
	if (move_right)
		field_moveCurrentTetrominoRight();
	if (hard_drop){
		field_hardDropCurrentTetromino();
		tickN = 0;
	}
	else if (soft_drop && tickN == 3){
		field_dropCurrentTetromino();
		tickN = 0;
	}
	else if (tickN == 6){
		field_dropCurrentTetromino();
		tickN = 0;
	}
	field_update();
	if (current_tetromino.placed){
		field_clearDetection();
		field_placeRandomTetromino();
	}
	hard_drop = 0;
	rotate = 0;
	move_left = 0;
	move_right = 0;
}

