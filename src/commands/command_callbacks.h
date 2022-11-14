//
// Created by alexium on 14.11.22.
//

#ifndef GOL__COMMAND_CALLBACKS_H_
#define GOL__COMMAND_CALLBACKS_H_

#include "CliCommand.h"

void command_dump(stringstream &ss, void **event_provider);
void command_tick(stringstream &ss, void **event_provider);
void command_exit(stringstream &ss, void **event_provider);
void command_resize(stringstream &ss, void **event_provider);
void command_rescale(stringstream &ss, void **event_provider);
void command_help(stringstream &ss, void **event_provider);
void command_hotkeys(stringstream &ss, void **event_provider);

#endif //GOL__COMMAND_CALLBACKS_H_
