//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_COMMANDS_COMMANDS_H_
#define GOL_SRC_COMMANDS_COMMANDS_H_

#include "CliCommand.h"
#include <vector>
#include <memory>

using namespace std;

extern vector<unique_ptr<CliCommand>> commands;

extern void add_commands();

#endif //GOL_SRC_COMMANDS_COMMANDS_H_
