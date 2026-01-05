#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "LPC17xx.h"

#define FIELD_H 20
#define FIELD_W 10
#define BLOCK_SIZE 15
#define FIELD_PADDING 10
#define FIELD_TOP_LEFT_X FIELD_PADDING
#define FIELD_TOP_LEFT_Y FIELD_PADDING
#define FIELD_TOP_RIGHT_X (FIELD_PADDING + BLOCK_SIZE * FIELD_W)
#define FIELD_TOP_RIGHT_Y FIELD_PADDING
#define FIELD_BOTTOM_LEFT_X FIELD_PADDING
#define FIELD_BOTTOM_LEFT_Y (FIELD_PADDING + BLOCK_SIZE * FIELD_H)
#define FIELD_BOTTOM_RIGHT_X (FIELD_PADDING + BLOCK_SIZE * FIELD_W)
#define FIELD_BOTTOM_RIGHT_Y (FIELD_PADDING + BLOCK_SIZE * FIELD_H)

typedef struct {
    uint8_t x;
    uint8_t y;
} cell_t;

typedef struct {
    uint8_t index;
    uint8_t rotation;
    uint8_t position_x;
    uint8_t position_y;
    uint8_t placed;
    uint16_t color;
} current_tetromino_t;

void field_init(void);
void scoreboard_init(void);

void advance_game(void);

void request_hardDrop(void);
void request_moveRight(void);
void request_moveLeft(void);
void request_rotate(void);
void set_softDrop(void);
void unset_softDrop(void);
void toggle_running(void);

#endif