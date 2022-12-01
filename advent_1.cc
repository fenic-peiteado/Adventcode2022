#include <fstream>
#include <iostream>
#include <vector>

//ADVENT OF CODE 2022
//DAY 1
int main() {
  std::fstream file_input;
  file_input.open("input", std::ios::in);
  std::string line;
  int result = 0;
  int max = 0;
  int max2 = 0;
  int max3 = 0;
  int sum = 0;
  while (std::getline(file_input, line)) {
    
    if(line.size() > 0) {
      int number = std::stoi(line);
      sum += number;
    }else{
      sum = 0;
    
    }
    if(sum > max) {
      max3 = max2;
      max2 = max;
      max = sum;
    }
    if(sum > max2 && sum < max) {
      max3 = max2;
      max2 = sum;
    }
    if(sum > max3 && sum < max2) {
      max3 = sum;
    }
    
  }
  std::cout  << max+max2+max3 << std::endl;
  return 0;
}