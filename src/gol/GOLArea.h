//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_GOL_GOLAREA_H_
#define GOL_SRC_GOL_GOLAREA_H_

#include "Cell.h"
#include <vector>
#include <fstream>

using namespace std;

class GOLArea {
 private:
  vector<vector<Cell>> cells;
  int sx, sy;
  string name;

  static int index(int i, int s);

 public:
  GOLArea(int sx,
          int sy,
          Rule alive_rules_set,
          Rule revive_rules_set,
          string name);

  pair<int, int> load(istream &in);

  void dump(ostream &out);

  friend ostream & operator<<(ostream &out, GOLArea &game);

  friend istream & operator>>(istream &in, GOLArea &game);

  void resize(int nx, int ny);

  void null_cells();

  int get_cell_count(int rx, int ry);

  Cell &get_cell(int x, int y);

  void revive_cell(int x, int y);

  void kill_cell(int x, int y);

  GOLArea(GOLArea &area);

  GOLArea();
};

#endif //GOL_SRC_GOL_GOLAREA_H_
