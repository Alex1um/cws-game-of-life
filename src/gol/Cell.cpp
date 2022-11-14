//
// Created by alexium on 14.11.22.
//

#include "Cell.h"

Cell::Cell(Rule alive_rules, Rule revive_rules) {
  alive = false;
  this->alive_rules = alive_rules;
  this->revive_rules = revive_rules;
}

bool Cell::is_alive() {
  return this->alive;
}

bool Cell::is_alive(int neighbour_count) {
  return this->alive_rules.is_in(neighbour_count);
}

bool Cell::is_can_be_revived(int neighbour_count) {
  return this->revive_rules.is_in(neighbour_count) && !this->alive;
}

void Cell::revive() {
  this->alive = true;
}

void Cell::kill() {
  this->alive = false;
}

Rule Cell::get_alive_rules() {
  return this->alive_rules;
}

Rule Cell::get_revive_rules() {
  return this->revive_rules;
}

void Cell::set_alive_rules(Rule rule) {
  this->alive_rules = rule;
}

void Cell::set_revive_rules(Rule rule) {
  this->revive_rules = rule;
}
