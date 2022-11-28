//
// Created by alexium on 14.11.22.
//

#include "game.h"
#include "globals.h"
#include "../commands/commands.h"

Game::Game(int sx, int sy, Rule alive, Rule revive) {
  scene = create_scene(sx, sy, 2);
  window = create_window(resolution_x, resolution_y);
  screen = create_screen();
  load_texture(&scene, &window, (char *) "../assets/dead.png");
  load_texture(&scene, &window, (char *) "../assets/alive.png");
  ids = vector<vector<ObjectId>>();
  for (int i = 0; i < sx; i++) {
    ids.emplace_back();
    for (int j = 0; j < sy; j++) {
      ids[i].push_back(create_object(&scene, i, j, 0, 0));
    }
  }
  add_commands();

  ticks = 0;
  this->sx = sx;
  this->sy = sy;
  area = GOLArea(sx, sy, alive, revive, "Standard area");
  new_area = GOLArea(area);
}

void Game::load_area(istream &in) {
  pair<int, int> tmp = area.load(in);
  resize(tmp.first, tmp.second);
  reset();
}

void Game::dump_area(ostream &out) {
  out << area;
}

ostream & operator<<(ostream &out, Game &game) {
  game.dump_area(out);
  return out;
}

istream & operator>>(istream &in, Game &game) {
  in >> game.area;
  return in;
}

void Game::tick() {
  ticks++;
  new_area.null_cells();
  for (int x = 0; x < this->sx; x++) {
    for (int y = 0; y < this->sy; y++) {
      int count = area.get_cell_count(x, y);
      if (area.get_cell(x, y).is_alive()) {
        if (area.get_cell(x, y).is_alive(count)) {
          new_area.revive_cell(x, y);
        }
      } else {
        if (area.get_cell(x, y).is_can_be_revived(count)) {
          new_area.revive_cell(x, y);
        }
      }
      switch (area.get_cell(x, y).is_alive()
          - new_area.get_cell(x, y).is_alive()) {
        case 1:change_type(&scene, get_id(x, y), 0);
          break;
        case -1:change_type(&scene, get_id(x, y), 1);
          break;
        case 0:break;
      }
    }
  }
  area = new_area;
}

void Game::full_update() {
  for (int x = 0; x < sx; x++) {
    for (int y = 0; y < sy; y++) {
      change_type(&scene, get_id(x, y), area.get_cell(x, y).is_alive());
    }
  }
  new_area = area;
}

void Game::reset() {
  ticks = 0;
  full_update();
}

void Game::add_cell(int x, int y) {
  area.revive_cell(x, y);
  change_type(&scene, get_id(x, y), 1);
}

void Game::resize(int nx, int ny) {
  for (int x = 0; x < sx; x++) {
    for (int y = 0; y < sy; y++) {
      remove_object(&scene, ids[x][y]);
    }
  }
  auto new_ids = vector<vector<ObjectId>>();
  scene_resize(&scene, nx, ny, 2);
  this->area.resize(nx, ny);
  for (int x = 0; x < nx; x++) {
    new_ids.emplace_back();
    for (int y = 0; y < ny; y++) {
      new_ids[x].push_back(create_object(&scene, x, y, 0, 0));
    }
  }
  ids = new_ids;
  sx = nx;
  sy = ny;
}

void Game::remove_cell(int x, int y) {
  area.kill_cell(x, y);
  change_type(&scene, get_id(x, y), 0);
}
bool Game::is_cell_alive(int x, int y) {
  return area.get_cell(x, y).is_alive();
}
int Game::get_size_x() const {
  return sx;
}
int Game::get_size_y() const {
  return sy;
}

