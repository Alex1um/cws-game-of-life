//
// Created by alexium on 14.11.22.
//

#ifndef GOL__GAME_H_
#define GOL__GAME_H_

#include "../gol/GOLArea.h"

extern "C" {
#include "../../../cws-rengines/engine.h"
}

class Game {
 private:
//  GOLArea area;
  GOLArea new_area;
  int sx, sy;
  unsigned long ticks = 0;
  vector<vector<ObjectId>> ids;

  unsigned long get_id(int x, int y) {
    return ids[x][y];
  }

 public:
  GOLArea area;
  void *scene;
  void *window;
  void *screen;

  Game(int sx, int sy, Rule alive, Rule revive);

  void load_area(istream &in);

 void dump_area(ostream &out);

  friend ostream & operator<<(ostream &out, Game &game);

  friend istream & operator>>(istream &in, Game &game);

  void tick();

  void full_update();

  void reset();

  void add_cell(int x, int y);

  void remove_cell(int x, int y);

  bool is_cell_alive(int x, int y);

  int get_size_x() const;

  int get_size_y() const;

  void resize(int nx, int ny);
};

#endif //GOL__GAME_H_
