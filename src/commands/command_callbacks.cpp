//
// Created by alexium on 14.11.22.
//
#include "command_callbacks.h"
#include "../game/globals.h"
#include "commands.h"
#include "CliCommand.h"

void CommandDump::execute(stringstream &ss, void **event_provider) {
  string buf;
  if (!(ss >> buf)) throw "no file name to output";
  ofstream out;
  out.open(buf.c_str());
  out << game;
//  game.area.dump(buf.c_str());
  output_file(buf.c_str());
}

CommandDump::CommandDump() {
  command = "dump";
}

void CommandDump::print_help() {
  cout << "<file name> - output current game state" << endl;
}

void CommandTick::execute(stringstream &ss, void **event_provider) {
  int tiks;
  if (ss >> tiks) {
    for (; tiks > 0; tiks--) {
      game.tick();
    }
  } else {
    game.tick();
  }
}

CommandTick::CommandTick() {
  command = "tick";
}

void CommandTick::print_help() {
  cout << "[n] - process 1(n) state(s) of the game" << endl;
}

void CommandExit::execute(stringstream &ss, void **event_provider) {
  throw_event(event_provider, Event{
      .type = EventType::Exit,
      .event = {},
  });
}

CommandExit::CommandExit() {
  command = "exit";
}

void CommandExit::print_help() {
  cout << "- stop game" << endl;
}

void CommandResize::execute(stringstream &ss, void **event_provider) {
  int nx, ny;
  if (!(ss >> nx >> ny)) throw "wrong sizes";
  game.resize(nx, ny);
  game.full_update();
}

CommandResize::CommandResize() {
  command = "resize";
}

void CommandResize::print_help() {
  cout << "<width> <height> - resize game with given sizes of board" << endl;
}

void CommandRescale::execute(stringstream &ss, void **event_provider) {
  float val;
  if (!(ss >> val)) throw "wrong value";
  scale = val;
  set_view_size(&game.screen, scale);
}

CommandRescale::CommandRescale() {
  command = "rescale";
}

void CommandRescale::print_help() {
  cout << "<ratio: float> - scale display game" << endl;
}

CommandHelp::CommandHelp() {
  command = "help";
}

void CommandHelp::print_help() {
  cout << "- prints help information for existing commands" << endl;
}

void CommandHelp::execute(stringstream &ss, void **event_provider) {
  for (unique_ptr<CliCommand> &cmd: commands) {
    cmd->print_help();
  }
}

CommandHotkeys::CommandHotkeys() {
  command = "hotkeys";
}

void CommandHotkeys::print_help() {
  cout << "- prints information about hotkeys" << endl;
}

void CommandHotkeys::execute(stringstream &ss, void **event_provider) {
  cout << "n - tick once" << endl
       << "r - reset size" << endl
       << "c - reset scale" << endl
       << "space - pause/resume" << endl
       << "mouse drag - move board" << endl
       << "mouse wheel - rescale board" << endl;
}
