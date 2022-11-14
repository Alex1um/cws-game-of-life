//
// Created by alexium on 14.11.22.
//

#include "Rule.h"

Rule::Rule(uint16_t rule) {
  str = rule;
}

Rule::Rule() {
  str = 0;
}

Rule::Rule(int array[], size_t length) {
  str = 0;
  for (int i = 0; i < length; i++) {
    str |= (1 << array[i]);
  }
}

Rule::Rule(int array[10]) {
  str = 0;
  for (int i = 0; i < 10; i++) {
    str |= (array[i] << i);
  }
}

Rule::Rule(std::string &s) {
  if (s.empty()) {
    str = 0b1111111111;
  } else {
    str = 0;
    for (auto c : s) {
      str |= 1 << (c - '0');
    }
  }
}

bool Rule::is_in(int e) const {
  return (1 << e) & str;
}

ostream &operator<<(ostream &os, Rule const &rule) {
  for (int i = 0; i < 10; i++) {
    if (rule.str & (1 << i)) {
      os << i;
    }
  }
  return os;
}
