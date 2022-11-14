//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_GAME_GLOBALS_H_
#define GOL_SRC_GAME_GLOBALS_H_

#include "game.h"

extern Game game;
extern unsigned long frame_rate;
extern unsigned long game_rate;
extern bool ticking;
extern bool dragging;
extern double scale;
extern int rel_x;
extern int rel_y;
extern bool is_mouse_was_moved;
extern int resolution_x;
extern int resolution_y;

#endif //GOL_SRC_GAME_GLOBALS_H_
