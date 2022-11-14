//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_GOL_CELL_H_
#define GOL_SRC_GOL_CELL_H_

#include "Rule.h"

class Cell {
 private:
  bool alive = false;
  Rule alive_rules;
  Rule revive_rules;

 public:

  Cell(Rule alive_rules, Rule revive_rules);

  bool is_alive();

  bool is_alive(int neighbour_count);

  bool is_can_be_revived(int neighbour_count);

  void revive();

  void kill();

  Rule get_alive_rules();

  Rule get_revive_rules();

  void set_alive_rules(Rule rule);

  void set_revive_rules(Rule rule);
};

#endif //GOL_SRC_GOL_CELL_H_
