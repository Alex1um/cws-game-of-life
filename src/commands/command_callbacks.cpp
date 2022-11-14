//
// Created by alexium on 14.11.22.
//
#include "command_callbacks.h"
#include "../game/globals.h"
#include "commands.h"
#include "CliCommand.h"

void command_dump(stringstream &ss, void **event_provider) {
  string buf;
  if (!(ss >> buf)) throw "no file name to output";
  game.area.dump(buf.c_str());
  output_file(buf.c_str());
}

void command_tick(stringstream &ss, void **event_provider) {
  int tiks;
  if (ss >> tiks) {
    for (; tiks > 0; tiks--) {
      game.tick();
    }
  } else {
    game.tick();
  }
}

void command_exit(stringstream &ss, void **event_provider) {
  throw_event(event_provider, Event{
      .type = EventType::Exit,
      .event = {},
  });
}

void command_resize(stringstream &ss, void **event_provider) {
  int nx, ny;
  if (!(ss >> nx >> ny)) throw "wrong sizes";
  game.resize(nx, ny);
  game.full_update();
}

void command_rescale(stringstream &ss, void **event_provider) {
  float val;
  if (!(ss >> val)) throw "wrong value";
  scale = val;
  set_view_size(&game.screen, scale);
}

void command_help(stringstream &ss, void **event_provider) {
  for (CliCommand &cmd : commands) {
    cmd.print_help();
  }
}

void command_hotkeys(stringstream &ss, void **event_provider) {
  cout << "n - tick once" << endl
       << "r - reset size" << endl
       << "c - reset scale" << endl
       << "space - pause/resume" << endl
       << "mouse drag - move board" << endl
       << "mouse wheel - rescale board" << endl;
}
