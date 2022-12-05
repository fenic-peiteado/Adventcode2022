#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

// advent of code day 5

int main() {
  std::ifstream input_file("input");
  std::string line;
  std::vector<std::string> input;
  std::vector<std::stack<std::string>> stack_input;

  for (int i = 0; i < 10; i++) {
    std::stack<std::string> stack_aux;
    stack_input.push_back(stack_aux);
  }
  int sum = 0;
  while (std::getline(input_file, line)) {
    if (line.size() == 0) {
      break;
    }
    int i = 1;
    std::string aux = line.substr(0, 3);
    line = line.substr(4);
    if (aux.find("[") != std::string::npos &&
        aux.find("]") != std::string::npos) {
      stack_input[i].push(aux);
    }
    i++;

    while (line.size() >= 3) {
      aux = line.substr(0, 3);

      if (line.size() == 3) {
        if (aux.find("[") != std::string::npos &&
            aux.find("]") != std::string::npos) {
          stack_input[i].push(aux);
        }
        i++;
        break;
      }
      line = line.substr(4);
      if (aux.find("[") != std::string::npos &&
          aux.find("]") != std::string::npos) {
        stack_input[i].push(aux);
      }
      i++;
    }
  }
  // Invertir los stacks
  for (int i = 0; i < 10; i++) {
    std::stack<std::string> stack_aux;
    while (!stack_input[i].empty()) {
      stack_aux.push(stack_input[i].top());
      stack_input[i].pop();
    }
    stack_input[i] = stack_aux;
  }

  while (std::getline(input_file, line)) {
    size_t pos = line.find(" ");
    line = line.substr(pos + 1);
    pos = line.find(" ");
    int move = std::stoi(line.substr(0, pos));
    line = line.substr(pos + 1);
    pos = line.find(" ");
    line = line.substr(pos + 1);
    pos = line.find(" ");
    int from2 = std::stoi(line.substr(0, pos));
    line = line.substr(pos + 1);
    pos = line.find(" ");
    int to2 = std::stoi(line.substr(pos + 1));
    std::stack<std::string> stack_aux;
    for (int i = 0; i < move; i++) {
      std::string aux = stack_input[from2].top();
      //PARTE 1
      /*
      std::string aux = stack_input[from2].top();
      stack_input[from2].pop();
      stack_input[to2].push(aux);
      */
      stack_input[from2].pop();
      stack_aux.push(aux);
    }
    while (!stack_aux.empty()) {
      stack_input[to2].push(stack_aux.top());
      stack_aux.pop();
    }

  }
  std::cout << "stack :" << std::endl;
  for (int i = 0; i < 10; i++) {
    if (!stack_input[i].empty()) {
      std::cout << stack_input[i].top()[1];
    }
  }
  return 0;
}