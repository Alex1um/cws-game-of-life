//
// Created by alexium on 14.11.22.
//

#include "GOLArea.h"

int GOLArea::index(int i, int s) {
  if (i < 0) return s + i;
  else return i % s;
}

GOLArea::GOLArea(int sx,
        int sy,
        Rule alive_rules_set,
        Rule revive_rules_set,
        string name) {
  this->sx = sx;
  this->name = std::move(name);
  this->sy = sy;
  cells = vector<vector<Cell>>();
  for (int x = 0; x < sx; x++) {
    cells.emplace_back();
    for (int y = 0; y < sy; y++) {
      cells[x].push_back(Cell(alive_rules_set, revive_rules_set));
    }
  }
}

void GOLArea::load(const string_view &file_name, int &size_x, int &size_y) {
  ifstream f;
  f.open(string(file_name));
  string line;
  if (!getline(f, line).good() || !getline(f, line).good()) {
    throw "file too short";
  }
  name = line.substr(3);
  if (!getline(f, line).good()) {
    throw "no rules / file too short";
  }
  auto slash_pos = line.find('/');
  string revive_pos = line.substr(4, slash_pos - 4);
  string alive_pos = line.substr(slash_pos + 2);
  Rule revive_rule = Rule(revive_pos);
  Rule alive_rule = Rule(alive_pos);
  for (int x = 0; x < sx; x++) {
    for (int y = 0; y < sy; y++) {
      cells[x][y].set_alive_rules(alive_rule);
      cells[x][y].set_revive_rules(revive_rule);
      cells[x][y].kill();
    }
  }
  vector<int> xes, yes;
  int nx = 0, ny = 0;
  int off_x = 0, off_y = 0;
  while (!f.eof()) {
    int x, y;
    f >> x >> y;
    xes.push_back(x);
    yes.push_back(y);
    if (nx < x) nx = x;
    if (ny < y) ny = y;
    if (x < 0 && -off_x > x) off_x = -x;
    if (y < 0 && -off_y > y) off_y = -y;
  }
  nx += off_x + 1;
  ny += off_y + 1;
  this->resize(nx, ny);
  for (size_t i = 0; i < xes.size(); i++) {
    cells[xes[i] + off_x][yes[i] + off_y].revive();
  }
  size_x = nx;
  size_y = ny;
  f.close();
}

void GOLArea::null_cells() {
  for (int x = 0; x < sx; x++) {
    for (int y = 0; y < sy; y++) {
      cells[x][y].kill();
    }
  }
}

int GOLArea::get_cell_count(int rx, int ry) {
  int count = -cells[rx][ry].is_alive();
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      bool val = cells[index(x + rx, sx)][index(y + ry, sy)].is_alive();
      count += val;
    }
  }
  return count;
}

Cell &GOLArea::get_cell(int x, int y) {
  return cells[x][y];
}

void GOLArea::revive_cell(int x, int y) {
  this->cells[x][y].revive();
}

void GOLArea::kill_cell(int x, int y) {
  this->cells[x][y].kill();
}

GOLArea::GOLArea(GOLArea &area) {
sx = area.sx;
sy = area.sy;
cells = area.cells;
name = area.name;
}

GOLArea::GOLArea() {}

void GOLArea::dump(const char *file) {
  ofstream f;
  f.open(file);
  f << "#Life 1.06" << endl;
  f << "#N " << this->name << endl;
  f << "#R B" << this->cells[0][0].get_revive_rules() << "/S"
    << this->cells[0][0].get_alive_rules() << endl;
  for (int x = 0; x < sx; x++) {
    for (int y = 0; y < sy; y++) {
      if (cells[x][y].is_alive()) {
        f << x << " " << y << endl;
      }
    }
  }
  f.close();
}

void GOLArea::resize(int nx, int ny) {
  if (nx > 0 && ny > 0) {
    auto new_cells = vector<vector<Cell>>();
    auto arules = cells[0][0].get_alive_rules();
    auto rrules = cells[0][0].get_revive_rules();
    for (int x = 0; x < nx; x++) {
      new_cells.emplace_back();
      for (int y = 0; y < ny; y++) {
        new_cells[x].push_back(Cell(arules, rrules));
        if (x < sx && y < sy && cells[x][y].is_alive())
          new_cells[x][y].revive();
      }
    }
    cells = new_cells;
    sx = nx;
    sy = ny;
  } else {
    throw "sizes less than or equal to 0";
  }
}
