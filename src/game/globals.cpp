//
// Created by alexium on 14.11.22.
//

#include "globals.h"

int resolution_x = 800;
int resolution_y = 600;
Game game = Game(20, 20, Rule(0b1100), Rule(0b1000));
unsigned long frame_rate = 60;
unsigned long game_rate = 10;
bool ticking = false;
bool dragging = false;
double scale = 1;
int rel_x = 0;
int rel_y = 0;
bool is_mouse_was_moved = false;
