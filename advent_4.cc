#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// advent of code day 4

bool parte2(std::pair<int, int> range1, std::pair<int, int> range2) {
  return (range1.first <= range2.second && range1.second >= range2.first);
}


//Tenia el codigo mas modular pero debido a fallo que tuve a la hora de pasarlo
// parte 1 decidir hacerlo todo en el main
int main() {
  // Read the input
  std::fstream input("input");
  std::string line;
  int sum = 0;
  std::vector<std::pair<int, int>> ranges;
  std::pair<int, int> words1;
  std::pair<int, int> words2;
  std::string s1, s2, aux, aux2;
   int sum2 = 0;
  while (std::getline(input, line)) {
    aux = line.substr(0, line.find(","));
    aux2 = line.substr(line.find(",") + 1, line.size());
    s1 = aux.substr(0, aux.find("-"));
    s2 = aux.substr(aux.find("-") + 1, aux.length());
    words1.first = std::stoi(s1);
    words1.second = std::stoi(s2);
    s1 = aux2.substr(0, aux2.find("-"));
    s2 = aux2.substr(aux2.find("-") + 1, aux2.length());
    words2.first = std::stoi(s1);
    words2.second = std::stoi(s2);

    if (words1.first <= words2.first && words1.second >= words2.second ||
        words2.first <= words1.first && words2.second >= words1.second) {
      sum++;
    }
   if (parte2(words1, words2)) {
      sum2++;
    }
  }


  std::cout << sum << std::endl;
  std::cout << sum2 << std::endl;


  return 0;
}