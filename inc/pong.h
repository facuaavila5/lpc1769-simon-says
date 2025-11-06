#ifndef PONG_H
#define PONG_H

#include "stdint.h"

#define ADDRESS_BANK_0 (uint32_t)0x2007C000
#define ADDRESS_BANK_1 (uint32_t)0x20080000
#define PADDLE_1_POS_X 0 // <- FIXME!
#define PADDLE_2_POS_X 0
#define BALL_POS_X 0
#define BALL_POS_Y 0


struct position {
    int32_t pos_x;
    int32_t pos_y;
};

struct velocity {
    int32_t veloc_x;
    int32_t veloc_y;
};

struct ball {
    struct velocity veloc;
    struct position pos;
};

struct paddle {
    struct position pos;
    struct velocity veloc;
    uint8_t score;
};

extern volatile struct ball ball;
extern volatile struct paddle player1, player2;


// function prototypes
void pong_init(void);
void init_ball(struct ball *);
void init_paddle(struct paddle *);

#endif
