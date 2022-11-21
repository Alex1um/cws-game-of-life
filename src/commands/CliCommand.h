//
// Created by alexium on 14.11.22.
//

#ifndef GOL__COMMAND_H_
#define GOL__COMMAND_H_

#include <iostream>
#include <sstream>
//#include <functional>
#include <utility>
//#include "command_callbacks.h"

using namespace std;

class CliCommand {
 private:
//  string command;
//  string help;
//  CommandCallbacks::callback_type callback;
 protected:
  string command;

 public:
//  CliCommand();

  virtual void print_help() = 0;

  bool is_it(string &cmd);

  bool operator==(string &cmd);

  virtual void execute(stringstream &ss, void **event_provider) = 0;
};

#endif //GOL__COMMAND_H_
