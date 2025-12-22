#ifndef __FIELD_H
#define __FIELD_H

#include "LPC17xx.h"

void field_init(void);
void field_setBlock(int x, int y, uint16_t color);
void field_update(void);
void field_placeTetromino(int x, int y, int idx, uint16_t color);

#endif
