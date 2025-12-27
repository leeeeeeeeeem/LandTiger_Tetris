#ifndef __FIELD_H
#define __FIELD_H

#include "LPC17xx.h"

void field_init(void);
void field_setBlock(int x, int y, uint16_t color);
void field_update(void);
void field_placeTetromino(uint8_t x, uint8_t y, uint8_t idx, uint8_t rotation, uint16_t color);
void field_dropCurrentTetromino(void);
void field_dropCurrentTetromino(void);
void field_moveCurrentTetrominoLeft(void);
void field_moveCurrentTetrominoRight(void);
void field_rotateCurrentTetromino(void);
void field_collisionDetection(void);
void field_clearDetection(void);
void field_clearRow(uint8_t y_toClear);

#endif
