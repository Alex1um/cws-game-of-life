//
// Created by alexium on 14.11.22.
//

#include "CliCommand.h"

//CliCommand::CliCommand() {};

//CliCommand::CliCommand(string command, string help, CommandCallbacks::callback_type callback) {
//this->command = std::move(command);
//this->help = std::move(help);
//this->callback = callback;
//}

//void CliCommand::print_help() {
//  cout << command << ' ' << help << endl;
//}

bool CliCommand::is_it(string &cmd) {
  return *this == cmd;
}

bool CliCommand::operator==(string &cmd) {
  return command == cmd;
}

//void CliCommand::execute(stringstream &ss, void **event_provider) {
//  this->callback(ss, event_provider);
//}


