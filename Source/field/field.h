#ifndef __FIELD_H
#define __FIELD_H

#include "LPC17xx.h"

void field_init(void);
void field_setBlock(int x, int y, uint16_t color);
void field_update(void);

#endif
