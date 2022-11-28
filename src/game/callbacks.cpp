//
// Created by alexium on 14.11.22.
//

#include "callbacks.h"
#include "globals.h"
#include "../commands/commands.h"
#include <iostream>

extern "C" {
void tick_callback(Event event, void **event_provider) {
  if (ticking && (frame_rate >= game_rate ?
      event.event.loop.tick % (frame_rate / game_rate) : 0) == 0)
    game.tick();
}

void toggle_ticking(Event event, void **event_provider) {
  ticking = !ticking;
}

void one_tick(Event event, void **event_provider) {
  game.tick();
}

void on_input_file(Event event, void **event_provider) {
  char *path = event.event.file_input.file_name;
//  int nx, ny;
//  game.area.load(path, nx, ny);
//  game.resize(nx, ny);
//  game.reset();
  ifstream f;
  f.open(path);
  f >> game;
//  game.load_area(string_view(string(path)));
}

void on_command(Event event, void **event_provider) {
  char *command = event.event.command.cmd;
  cout << "> " << command << endl;
  string incmd;
  stringstream ss = stringstream(command);
  if (!(ss >> incmd)) {
    cout << "command is empty" << endl;
    return;
  }
  try {
    for (unique_ptr<CliCommand> &cmd : commands) {
      if (*cmd == incmd) {
        cmd->execute(ss, event_provider);
        return;
      }
    }
    cout << "wrong command" << endl;
  } catch (const char *exc) {
    cout << exc << endl;
  }
}

void rescale(Event event, void **event_provider) {
  float dir = event.event.mouse_wheel.y_dir;
  if (dir > 0) scale *= 1.05;
  else if (dir < 0) scale /= 1.05;
  set_view_size(&game.screen, scale);
}

void drag_switcher(Event event, void **event_provider) {
  if (event.type == EventType::MouseButtonDown) {
    dragging = true;
  }
  if (event.type == EventType::MouseButtonUp) {
    dragging = false;
  }
}

void drag(Event event, void **event_provider) {
  if (dragging) {
    is_mouse_was_moved = true;
    rel_x += event.event.mouse_motion.x_rel;
    rel_y += event.event.mouse_motion.y_rel;
    set_view_pos(&game.screen, rel_x - resolution_x, rel_y - resolution_y);
  }
}

void cell_switch_on_click(Event event, void **event_provider) {
  if (!is_mouse_was_moved) {
    int click_x = event.event.mouse_button.x;
    int click_y = event.event.mouse_button.y;
    int sx = game.get_size_x();
    int sy = game.get_size_y();
    int x = (int)((double)(click_x - rel_x) / ((double)(resolution_x - (resolution_x % sx)) * scale) * (double)sx );
    int y = (int)((double)(click_y - rel_y) / ((double)(resolution_y - (resolution_y % sy)) * scale) * (double)sy);
    if (x >= 0 && x < game.get_size_x() && y >= 0 && y < game.get_size_y()) {
      if (game.is_cell_alive(x, y)) game.remove_cell(x, y);
      else game.add_cell(x, y);
    }
  } else {
    is_mouse_was_moved = false;
  }
}

void reset_board_pos(Event event, void **event_provider) {
  rel_x = 0;
  rel_y = 0;
  set_view_pos(&game.screen, -resolution_x, -resolution_y);
}

void reset_board_scale(Event event, void **event_provider) {
  scale = 1;
  set_view_size(&game.screen, scale);
}

}
