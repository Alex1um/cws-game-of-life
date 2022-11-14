//
// Created by alexium on 14.11.22.
//

#include "commands.h"
#include "command_callbacks.h"
#include <vector>

std::vector<CliCommand> commands {
    CliCommand("help", "- prints help information for existing commands", command_help),
    CliCommand("hotkeys", "- prints information about hotkeys", command_hotkeys),
    CliCommand("rescale", "<ratio: float> - scale display game", command_rescale),
    CliCommand("resize", "<width> <height> - resize game with given sizes of board", command_resize),
    CliCommand("tick", "[n] - process 1(n) state(s) of the game", command_tick),
    CliCommand("dump", "<file name> - output current game state", command_dump),
    CliCommand("exit", "- stop game", command_exit),
};
