//
// Created by alexium on 14.11.22.
//

#ifndef GOL__COMMAND_H_
#define GOL__COMMAND_H_

#include <iostream>
#include <sstream>
//#include <functional>
#include <utility>
#include "command_callbacks.h"

using namespace std;

class CliCommand {
 private:
  string command;
  string help;
  CommandCallbacks::callback_type callback;
 public:
  CliCommand(string command, string help, CommandCallbacks::callback_type callback);

  void print_help();

  bool is_it(string &cmd);

  bool operator==(string &cmd);

  void execute(stringstream &ss, void **event_provider);
};

#endif //GOL__COMMAND_H_
