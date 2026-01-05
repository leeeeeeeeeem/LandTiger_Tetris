#include "field.h"
#include "GLCD.h"
#include <stdlib.h>
#include <stdio.h>

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
    0xADDE,
    0xF6F5,
    0xC53E,
    0x859E,
    0xF590,
    0xA713,
    0xEC54,
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

uint32_t current_score;
uint32_t high_score = 0;
uint8_t total_cleared_rows = 0;

uint32_t seed;

uint8_t paused_placed = 0;

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

void field_reset(){
	uint8_t y, x;
    for (y = 0; y < FIELD_H; y++) {
        for (x = 0; x < FIELD_W; x++) {
			if (field[y][x] != Black)
				field_setBlock(x, y, 0xFFFF);
        }
    }
}

void field_update(){
	uint8_t i, x, y;
	for (i = 0; i < toPlace_count; i++) {
		x = toPlace[i].x;
		y = toPlace[i].y;
		if (field[y][x] == 0xFFFF) {
			set_block(FIELD_TOP_LEFT_X + BLOCK_SIZE * x, FIELD_TOP_LEFT_Y + BLOCK_SIZE * y, BLOCK_SIZE, Black);
			field[y][x] = Black;
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
			field[y][x] = Black;
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
	if (idx == current_tetromino.index)
		idx++;
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
				if (field[current_y][current_x] != Black && 
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
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x + 1] != Black &&
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
						 field[current_tetromino.position_y + y][current_tetromino.position_x + x - 1] != Black &&
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
					 (field[current_tetromino.position_y + y + 1][current_tetromino.position_x + x] != Black &&
					  field[current_tetromino.position_y + y + 1][current_tetromino.position_x + x] != 0xFFFF)
					)
				) 
						current_tetromino.placed = 1;
		}
	}
}

uint8_t field_clearDetection(){
    uint8_t y, x, cleared, cleared_rows = 0;
    for (y = 0; y < FIELD_H; y++){
        cleared = 1;
        for (x = 0; x < FIELD_W; x++){
            if (field[y][x] == Black || field[y][x] == 0xFFFF)
                cleared = 0;
        }
        if (cleared){
            field_clearRow(y);
			cleared_rows++;
		}
    }
	return cleared_rows;
}

void field_clearRow(uint8_t y_toClear){
    uint8_t y, x;
    for (y = y_toClear; y > 0; y--) {
        for (x = 0; x < FIELD_W; x++) {
            if (field[y - 1][x] == Black && field[y][x] != Black)
                field_setBlock(x, y, 0xFFFF); 
			else if (field[y - 1][x] != Black)
                field_setBlock(x, y, field[y - 1][x]);
        }
    }
    for (x = 0; x < FIELD_W; x++) {
        field_setBlock(x, 0, 0xFFFF);
    }
    field_update();
}

void field_gameEndDetection(){
	if (current_tetromino.position_y <= 0)
		reset_game();
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
	current_score = 0;
	total_cleared_rows = 0;
	game_started = 1;
	tickN = 0;
	current_tetromino.index = 10;
	field_placeRandomTetromino();
}

void reset_game(){
	game_running = 0;
	game_started = 0;
	if (current_score > high_score)
		high_score = current_score;
	current_score = 0;
	total_cleared_rows = 0;
	scoreboard_update();
	field_reset();
	field_update();
}

void advance_game(){
	uint8_t cleared_rows;
	if (!game_running){
		GUI_Text(170, 10, (uint8_t*) "paused", Grey, Black); 
		paused_placed = 1;
		return;
	}
	if (paused_placed){
		GUI_Text(170, 10, (uint8_t*) "paused", Black, Black); 
		paused_placed = 0;
	}
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
		current_score += 10;
		cleared_rows = field_clearDetection();
		total_cleared_rows += cleared_rows;
		while (cleared_rows >= 4){
			current_score += 600;
			cleared_rows -= 4;
		}
		current_score += cleared_rows * 100;
		scoreboard_update();
		field_gameEndDetection();
		if (game_started)
			field_placeRandomTetromino();
	}
	hard_drop = 0;
	rotate = 0;
	move_left = 0;
	move_right = 0;
}

void scoreboard_init(){
	GUI_Text(170, 70, (uint8_t*) "high", Grey, Black); 
	GUI_Text(170, 90, (uint8_t*) "score", Grey, Black); 
	GUI_Text(170, 110, (uint8_t*) "0", Grey, Black); 
	GUI_Text(170, 150, (uint8_t*) "score", Grey, Black); 
	GUI_Text(170, 170, (uint8_t*) "0", Grey, Black); 
	GUI_Text(170, 210, (uint8_t*) "cleared", Grey, Black); 
	GUI_Text(170, 230, (uint8_t*) "0", Grey, Black); 
}

void scoreboard_update(){
	char high_score_string[7], score_string[7], cleared_string[7];
	sprintf(high_score_string, "%-6d", high_score);
	sprintf(score_string, "%-6d", current_score);
	sprintf(cleared_string, "%-6d", total_cleared_rows);
	GUI_Text(170, 110, (uint8_t*) high_score_string, Grey, Black); 
	GUI_Text(170, 170, (uint8_t*) score_string, Grey, Black); 
	GUI_Text(170, 230, (uint8_t*) cleared_string, Grey, Black); 
}

