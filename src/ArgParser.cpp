//
// Created by alexium on 14.11.22.
//

#include "ArgParser.h"
#include <iostream>

ArgParser::ArgParser(int argc, char **kwargs) {
  string_view found_key = string_view();
  for (int i = 1; i < argc; i++) {
    string_view arg = kwargs[i];
    size_t len = arg.length();
    if (!found_key.empty()) {
      parsed_args[found_key] = arg;
      found_key = string_view();
    } else if (arg[0] == '-') {
      if (len > 1) {
        if (arg[1] == '-') {
          size_t eq_pos = arg.find('=');
          if (eq_pos == -1) throw "Expected '=' in argument but not found";
          else {
            parsed_args[arg.substr(0, eq_pos)] =
                arg.substr(eq_pos + 1, len - eq_pos - 1);
          }
        } else {
          found_key = arg;
        }
      } else {
        throw "Wrong argument '-'";
      }
    } else {
      anonymous_args.push_back(arg);
//      throw "Unexpected argument";
    }
  }
}

string_view ArgParser::get(const string_view &key) {
  return parsed_args[key];
}

string_view ArgParser::get(const string_view &key1, const string_view &key2) {
  string_view sv = get(key1);
  if (!sv.empty()) return sv;
  else return get(key2);
}

string_view ArgParser::get_anonymous_arg(int index) {
  if (anonymous_args.size() > index) return anonymous_args[index];
  else throw "argument count is less than requested";
}
