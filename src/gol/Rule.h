//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_GOL_RULE_H_
#define GOL_SRC_GOL_RULE_H_

#include <cstdint>
#include <ostream>

using namespace std;

class Rule {
 private:
  uint16_t str = 0;
 public:
  Rule(uint16_t rule);

  Rule();

  Rule(int array[], size_t length);

  Rule(int array[10]);

  Rule(string &s);

  bool is_in(int e) const;

  friend ostream &operator<<(ostream &os, Rule const &rule);
};

#endif //GOL_SRC_GOL_RULE_H_
