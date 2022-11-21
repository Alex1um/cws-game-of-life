#include "game/globals.h"
#include "game/callbacks.h"
#include "ArgParser.h"
#include <iostream>

void start_game() {
  auto loop =
      create_event_loop(&game.scene, &game.window, &game.screen, frame_rate);
  add_event_listener(&loop,
                     Event{EventType::Loop, EventContainer{}},
                     tick_callback);
  add_event_listener(&loop,
                     Event{.type = EventType::KeyboardButtonDown,
                         .event = EventContainer{
                             .keyboard_button.key = 32,
                         }
                     }, toggle_ticking);
  add_event_listener(&loop,
                     Event{.type = EventType::KeyboardButtonDown,
                         .event = EventContainer{
                             .keyboard_button.key = 114,
                         }
                     }, reset_board_scale);
  add_event_listener(&loop,
                     Event{.type = EventType::KeyboardButtonDown,
                         .event = EventContainer{
                             .keyboard_button.key = 99,
                         }
                     }, reset_board_pos);
  add_event_listener(&loop,
                     Event{.type = EventType::KeyboardButtonUp,
                         .event = EventContainer{
                             .keyboard_button.key = 110,
                         }
                     }, one_tick);
//  add_keyboard_listener(&loop, 32, toggle_ticking);
//  add_keyboard_listener(&loop, 110, one_tick);
  add_console_input_provider(&loop);
  add_file_input_provider(&loop);

  add_event_listener(&loop,
                     Event{.type = EventType::Command,
                         .event = EventContainer{
                             .command.cmd = "",
                         }}, on_command);

  add_event_listener(&loop,
                     Event{.type = EventType::FileInput,
                         .event = EventContainer{
                             .file_input.file_name = "",
                         }}, on_input_file);

  add_event_listener(&loop,
                     Event{.type = EventType::MouseWheel,
                         .event = EventContainer{
                             0,
                         }}, rescale);

  add_event_listener(&loop,
                     Event{.type = EventType::MouseButtonDown,
                         .event = EventContainer{
                             .mouse_button.key = 1,
                         }}, drag_switcher);

  add_event_listener(&loop,
                     Event{.type = EventType::MouseButtonUp,
                         .event = EventContainer{
                             .mouse_button.key = 1,
                         }}, drag_switcher);


  add_event_listener(&loop,
                     Event{.type = EventType::MouseButtonUp,
                         .event = EventContainer{
                             .mouse_button.key = 1,
                         }}, cell_switch_on_click);

  add_event_listener(&loop,
                     Event{.type = EventType::MouseMotion,
                         .event = EventContainer{
                             0
                         }}, drag);

  start_event_loop(loop);
};

int main(int argc, char *argv[]) {
  string_view iterations = string_view();
  string_view output_file = string_view();
  string_view input_file = string_view();
  try {
    auto args = ArgParser(argc, argv);
    output_file = args.get("-o", "--output");
    iterations = args.get("-i", "--iterations");
    input_file = args.get_anonymous_arg(0);
  } catch (const char *exc) {
    cout << exc << endl;
  }

  bool error_while_loading_input_file = false;
  if (!input_file.empty()) {
    try {
      game.load_area(input_file);
    } catch (const char *exc) {
      cout << "Error while loading area from args: " << exc << endl;
      error_while_loading_input_file = true;
    }
  } else {
    error_while_loading_input_file = true;
  }
  if (error_while_loading_input_file) {
    cout << "Loading default state..." << endl;
    game.add_cell(1, 0);
    game.add_cell(2, 0);
    game.add_cell(3, 0);

    game.add_cell(5, 7);
    game.add_cell(4, 5);
    game.add_cell(5, 5);
    game.add_cell(6, 5);
    game.add_cell(6, 6);
  }

  if (!iterations.empty()) {
    size_t ticks;
    if (sscanf(string(iterations).c_str(), "%ld", &ticks) == 1) {
      for (;ticks > 0; ticks -- ) {
        game.tick();
      }
    } else {
      cout << "wrong iterations value" << endl;
    }

    if (!output_file.empty()) {
      try {
        game.area.dump(string(output_file).c_str());
      } catch (const char *exc) {
        cout << "Exception while outputting file from args: " << exc << endl;
      }
    }
  }

  start_game();
}

class A {
 public:
  virtual void foo() = 0;
  ~A() {}
  A() {}
};

class B : public A {
  void foo() override {
    cout << "B!" << endl;
  }
};

class C : public A {
  void foo() override {
    cout << "C!" << endl;
  }
};

//#include <memory>
//
//vector<unique_ptr<A>> gl{
//    unique_ptr<A>(new B()),
//    unique_ptr<A>(new C()),
//};
//
//int main() {
//  gl.push_back(unique_ptr<A>(new B()));
//  gl.push_back(unique_ptr<A>(new C()));
//  gl[0]->foo();
//  gl[1]->foo();
//}