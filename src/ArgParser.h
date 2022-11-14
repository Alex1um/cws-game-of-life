//
// Created by alexium on 14.11.22.
//

#ifndef GOL_SRC_ARGPARSER_H_
#define GOL_SRC_ARGPARSER_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

class ArgParser {
 private:
  map<string_view, string_view> parsed_args;
  vector<string_view> anonymous_args;
 public:
  ArgParser(int args, char *kwargs[]);

  string_view get(const string_view &key);

  string_view get(const string_view &key1, const string_view &key2);

  string_view get_anonymous_arg(int index);
};

#endif //GOL_SRC_ARGPARSER_H_
