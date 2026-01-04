#ifndef __FIELD_H
#define __FIELD_H

#include "LPC17xx.h"

void field_init(void);
void field_setBlock(int x, int y, uint16_t color);
void field_update(void);
void field_placeTetromino(uint8_t x, uint8_t y, uint8_t idx, uint8_t rotation, uint16_t color, uint8_t update);
uint8_t generate_idx(void);
void field_placeRandomTetromino(void);
void field_dropCurrentTetromino(void);
void field_hardDropCurrentTetromino(void);
void field_moveCurrentTetrominoLeft(void);
void field_moveCurrentTetrominoRight(void);
void field_rotateCurrentTetromino(void);
void field_collisionDetection(void);
uint8_t field_clearDetection(void);
void field_clearRow(uint8_t y_toClear);
void reset_game(void);
void request_hardDrop(void);
void request_moveRight(void);
void request_moveLeft(void);
void request_rotate(void);
void set_softDrop(void);
void unset_softDrop(void);
void toggle_running(void);
void start_game(void);
void advance_game(void);


#endif
