//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_GAME_CALLBACKS_H_
#define GOL_SRC_GAME_CALLBACKS_H_

extern "C" {

#include "../../../cws-rengines/engine.h"

void tick_callback(Event event, void **event_provider);

void toggle_ticking(Event event, void **event_provider);

void one_tick(Event event, void **event_provider);

void on_input_file(Event event, void **event_provider);

void on_command(Event event, void **event_provider);

void rescale(Event event, void **event_provider);

void drag_switcher(Event event, void **event_provider);

void drag(Event event, void **event_provider);

void reset_board_pos(Event event, void **event_provider);

void reset_board_scale(Event event, void **event_provider);

void cell_switch_on_click(Event event, void **event_provider);
}
#endif //GOL_SRC_GAME_CALLBACKS_H_
