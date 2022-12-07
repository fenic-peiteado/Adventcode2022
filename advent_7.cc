#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

// advent of code day 7

int main() {
  std::ifstream input_file("input");
  std::string line;
  std::regex rgx("[0-9]+");
  std::vector<size_t> size_dir_vector;
  std::map<std::string, size_t> dir;
  std::stack<std::string> dir_stack;
  std::regex rgx_dir("cd");
  std::regex rgx_ant("cd\\s..$");
  size_t sum = 0;
  size_t sum_no = 0;
  std::string dir_name;
  while (std::getline(input_file, line)) {
    std::smatch match;
    if (std::regex_search(line, match, rgx_dir)) {
      if (std::regex_search(line, match, rgx_ant)) {
        size_t aux = dir[dir_stack.top()];
        dir_stack.pop();
        dir[dir_stack.top()] = aux + dir[dir_stack.top()];
        continue;
      }
      // Substraer el nombre del directorio con regex
      std::regex rgx_dir_name("\\$\\scd\\s");
      std::string direc_name = std::regex_replace(line, rgx_dir_name, "");
      dir_name = direc_name;
      if (dir_stack.empty()) {
        dir[dir_name] = 0;
      } else {
        if (dir_stack.top() == "/") {
          dir[dir_stack.top() + dir_name] = 0;
          dir_name = dir_stack.top() + dir_name;
        } else {
          dir[dir_stack.top() + "/" + dir_name] = 0;
          dir_name = dir_stack.top() + "/" + dir_name;
        }
      }
      dir_stack.push(dir_name);
    }
    if (std::regex_search(line, match, rgx)) {
      sum_no = std::stoi(match.str());
      dir[dir_name] += sum_no;
    }
  }

  while (!dir_stack.empty()) {
    size_t aux = dir[dir_stack.top()];
    dir_stack.pop();
    if (dir_stack.empty()) {
      break;
    }
    dir[dir_stack.top()] = aux + dir[dir_stack.top()];
  }

  size_t final_sum = 0;
  for (auto const& x : dir) {
    std::cout << x.first << " " << x.second << std::endl;
    size_dir_vector.push_back(x.second);
    if (x.second <= 100000) {
      final_sum += x.second;
    }
  }
  size_t space_max = 70000000;
  size_t need_space = 30000000;
  size_t space_used = dir["/"];
  size_t space_available = space_max - space_used;
  std::sort(size_dir_vector.begin(), size_dir_vector.end());
  for (auto const& x : size_dir_vector) {
  
    if(space_available + x >= need_space){
      std::cout << "Parte 2: " << x << std::endl;
      break;
    }
  }

  std::cout << "Parte 1: " << final_sum << std::endl;
  return 0;
}
