//
// Created by alexium on 14.11.22.
//

#ifndef GOL__COMMAND_CALLBACKS_H_
#define GOL__COMMAND_CALLBACKS_H_

#include <sstream>
#include "CliCommand.h"

using namespace std;

//class CommandCallbacks final{
// public:
//  typedef void (*callback_type)(stringstream &ss, void **event_provider);
//
//  static void help(stringstream &ss, void **event_provider);
//
//  static void dump(stringstream &ss, void **event_provider);
//
//  static void tick(stringstream &ss, void **event_provider);
//  static void exit(stringstream &ss, void **event_provider);
//  static void resize(stringstream &ss, void **event_provider);
//  static void rescale(stringstream &ss, void **event_provider);
//  static void hotkeys(stringstream &ss, void **event_provider);
//
//};

class CommandHotkeys : public CliCommand {
 public:
  CommandHotkeys();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandRescale : public CliCommand {
 public:
  CommandRescale();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandResize : public CliCommand {
 public:
  CommandResize();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandDump : public CliCommand {
 public:
  CommandDump();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandTick : public CliCommand {
 public:
  CommandTick();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandExit : public CliCommand {
 public:
  CommandExit();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

class CommandHelp : public CliCommand {
 public:
  CommandHelp();

  void execute(stringstream &ss, void **event_provider) override;

  void print_help() override;
};

#endif //GOL__COMMAND_CALLBACKS_H_
