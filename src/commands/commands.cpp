//
// Created by alexium on 14.11.22.
//

#include "commands.h"
#include "command_callbacks.h"

std::vector<unique_ptr<CliCommand>> commands {
//    CliCommand("help", "- prints help information for existing commands", CommandCallbacks::help),
//    CliCommand("hotkeys", "- prints information about hotkeys", CommandCallbacks::hotkeys),
//    CliCommand("rescale", "<ratio: float> - scale display game", CommandCallbacks::rescale),
//    CliCommand("resize", "<width> <height> - resize game with given sizes of board", CommandCallbacks::resize),
//    CliCommand("tick", "[n] - process 1(n) state(s) of the game", CommandCallbacks::tick),
//    CliCommand("dump", "<file name> - output current game state", CommandCallbacks::dump),
//    CliCommand("exit", "- stop game", CommandCallbacks::exit),
};

void add_commands() {
  commands.push_back(unique_ptr<CliCommand>(new CommandHelp()));
  commands.push_back(unique_ptr<CliCommand>(new CommandHotkeys()));
  commands.push_back(unique_ptr<CliCommand>(new CommandRescale()));
  commands.push_back(unique_ptr<CliCommand>(new CommandResize()));
  commands.push_back(unique_ptr<CliCommand>(new CommandTick()));
  commands.push_back(unique_ptr<CliCommand>(new CommandDump()));
  commands.push_back(unique_ptr<CliCommand>(new CommandExit()));
};
