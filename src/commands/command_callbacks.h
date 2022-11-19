//
// Created by alexium on 14.11.22.
//

#ifndef GOL__COMMAND_CALLBACKS_H_
#define GOL__COMMAND_CALLBACKS_H_

#include <sstream>

using namespace std;

class CommandCallbacks final{
 public:
  typedef void (*callback_type)(stringstream &ss, void **event_provider);

  static void help(stringstream &ss, void **event_provider);

  static void dump(stringstream &ss, void **event_provider);

  static void tick(stringstream &ss, void **event_provider);
  static void exit(stringstream &ss, void **event_provider);
  static void resize(stringstream &ss, void **event_provider);
  static void rescale(stringstream &ss, void **event_provider);
  static void hotkeys(stringstream &ss, void **event_provider);

};

#endif //GOL__COMMAND_CALLBACKS_H_
