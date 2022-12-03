#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
// ADVENT OF CODE DAY 3 2022
int ValueSet(std::vector<char> set_final);
std::vector<char> Parte1(std::ifstream &input);
std::vector<char> Parte2(std::ifstream &input);

int main() {
  std::ifstream input("prueba");
  std::ifstream input2("prueba");
  std::vector<char> result;
  std::vector<char> result2;

  result = Parte1(input);
  result2 = Parte2(input2);

  std::cout << "Parte 1:" << ValueSet(result) << std::endl;
  std::cout << "Parte 2:" << ValueSet(result2) << std::endl;
  input.close();
  input2.close();
  return 0;
}

std::vector<char> Parte1(std::ifstream &input) {
  std::set<char> result;
  std::vector<char> set_final;
  std::string line;
  while (std::getline(input, line)) {
    std::set<char> first;
    std::set<char> second;
    for (int i = 0; i < line.size() / 2; i++) {
      first.insert(line[i]);
    }
    for (int i = line.size() / 2; i < line.size(); i++) {
      second.insert(line[i]);
    }
    std::set<char> intersection;
    std::set_intersection(first.begin(), first.end(), second.begin(),
                          second.end(),
                          std::inserter(intersection, intersection.begin()));
    for (auto i : intersection) {
      set_final.push_back(i);
    }
  }
  return set_final;
}

int ValueSet(std::vector<char> set_final) {
  size_t encounter;
  int result = 0;
  for (auto i : set_final) {
    if (i >= 'a' && i <= 'z') {
      result = result + i - 96;
    } else {
      result = result + i - 64 + 26;
    }
  }
  return result;
}

std::vector<char> Parte2(std::ifstream &input) {
  std::set<char> result;
  std::vector<char> set_final;
  std::string line;
  while (std::getline(input, line)) {
    std::set<char> first;
    std::set<char> second;
    std::set<char> third;
    for (int i = 0; i < line.size(); i++) {
      first.insert(line[i]);
    }
    std::getline(input, line);
    for (int i = 0; i < line.size(); i++) {
      second.insert(line[i]);
    }
    std::getline(input, line);
    for (int i = 0; i < line.size(); i++) {
      third.insert(line[i]);
    }

    std::set<char> intersection;
    std::set_intersection(first.begin(), first.end(), second.begin(),
                          second.end(),
                          std::inserter(intersection, intersection.begin()));
    std::set<char> intersection2;
    std::set_intersection(intersection.begin(), intersection.end(),
                          third.begin(), third.end(),
                          std::inserter(intersection2, intersection2.begin()));
    for (auto i : intersection2) {
      std::cout << i << std::endl;
      set_final.push_back(i);
    }
  }
  return set_final;
}