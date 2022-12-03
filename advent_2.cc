#include <fstream>
#include <iostream>
#include <vector>

// ADVENT OF CODE 2022
// DAY 2
int ppt(char a, char b) {
  if (a == 'A' && b == 'Z' || a == 'B' && b == 'X' || a == 'C' && b == 'Y')
    return 1;
  else if (a == 'B' && b == 'Z' || a == 'C' && b == 'X' || a == 'A' && b == 'Y')
    return 2;
  else
    return 0;
}




int main() {
  std::fstream file_input;
  file_input.open("input", std::ios::in);
  std::string line;
  int sum = 0;
  int sum2 = 0;
  char c, u;
  int c_, v_;
  while (std::getline(file_input, line)) {
    c = line[0];
    u = line[2];
    std::cout << c << " " << u << std::endl;
    switch (c) {
      case 'A':
        c_ = 1;
        break;
      case 'B':
        c_ = 2;
        break;
      case 'C':
        c_ = 3;
        break;
    }
    std::cout << c_ << std::endl;
    switch (u) {
      case 'Y':
        v_ = 2;
        sum2 = sum2 + 3 + (c - 64);
        break;
      case 'X':
      if (c_ == 1) {
        sum2 = sum2  + (c - 64)+2;
      } else {
        sum2 = sum2  + (c - 64)-1;
      }
        v_ = 1;
        break;
      case 'Z':
        v_ = 3;
        sum2 = sum2 + 6 + (c - 64) % 3 + 1;
        break;
    }

    if (ppt(c, u) == 1) {  // Perder
      // std::cout << "Perder" << std::endl;
      sum = sum + v_ + 0;
    } else if (ppt(c, u) == 2) {  // ganar
      sum = sum + v_ + 6;
    } else if (ppt(c, u) == 0) {
      sum = sum + v_ + 3;
    }
  }
  std::cout << sum << std::endl;
  std::cout << sum2 << std::endl;
  return 0;
}