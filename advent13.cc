#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// advent of code 2022 day 13
// https://adventofcode.com/2020/day/13

// Leer pares de lineas y comparar sus valores
// la primera linea se llama izquierda y la segunda derecha son una secuencia de
// numeros separados por comas y corchete si la izquierda es menor que la
// derecha, es correcto y en caso contrario es incorrecto Si es igual se sigue
// analizando la lista de valores Si la izquierda esta vacia, es correcto Si
// estan vacias las dos son incorrectas

// ejemplo
//[1,1,3,1,1]
//[1,1,5,1,1]
// correcto ya que compara todo la secuencia hasta el 3 y 5 y la izquierda es
// menor que la derecha Vamos utiliza una vector de pares de lista de enteros

std::vector<std::pair<std::queue<int>, std::queue<int>>> Datos;

int main() {
  std::ifstream file("input");
  std::string line;
  // Para cada par de lineas solo leemos los numeros por lo que quitamos los
  // corchetes y dejamos la coma como separador
  while (std::getline(file, line)) {
    std::string line2;
    std::getline(file, line2);
    std::regex regcorchete1("\\[");
    std::regex regcorchete2("\\]");
    std::regex regespacio(" ");

    line = std::regex_replace(line, regcorchete1, "");
    line = std::regex_replace(line, regcorchete2, "");
    line = std::regex_replace(line, regespacio, "");
    line2 = std::regex_replace(line2, regcorchete1, "");
    line2 = std::regex_replace(line2, regcorchete2, "");
    line2 = std::regex_replace(line2, regespacio, "");

    // Ahora leemos los numeros de cada linea separados por comas y los metemos
    // en su cola;
    //  std::cout << line << " " << line.size() << std::endl;
    //  std::cout << line2 << " " << line2.size() << std::endl;
    std::stringstream ss(line);
    std::stringstream ss2(line2);
    std::string token;
    std::queue<int> cola;
    std::queue<int> cola2;
    while (std::getline(ss, token, ',')) {
      if (token == " " || token.size() == 0) {
        continue;
      }
      cola.push(std::stoi(token));
    }
    while (std::getline(ss2, token, ',')) {
      if (token == " " || token.size() == 0) {
        continue;
      }
      cola2.push(std::stoi(token));
    }
    Datos.push_back(std::make_pair(cola, cola2));
    // Ahora hacemos el salto de linea
    std::getline(file, line);
  }
  // Ahora recorremos el vector de pares de colas y comparamos los valores
  int i = 1;
  int suma = 0;
  for (auto &par : Datos) {
    std::queue<int> cola = par.first;
    std::queue<int> cola2 = par.second;
    bool correcto = false;
    if (cola.empty() && cola2.empty()) {
      correcto = false;
      goto salida;
    }
    if (cola.empty()) {
      correcto = true;
      goto salida;
    }else if (cola2.empty()) {
      correcto = false;
      goto salida;
    }
    while (!cola.empty() && !cola2.empty()) {
      if (cola.front() == cola2.front()) {
        cola.pop();
        cola2.pop();
      } else if (cola.front() < cola2.front()) {
        correcto = true;
        goto salida;
      } else {
        correcto = false;
        goto salida;
      }
      if (cola.empty() && cola2.empty()) {
        correcto = false;
        goto salida;
      } else if (cola.empty()) {
        correcto = true;
        goto salida;
      } else if (cola2.empty()) {
        correcto = false;
        goto salida;
      }
    }
  salida:
    if (correcto) {
      std::cout << "correcto" << std::endl;
      suma += i;
    } else {
      std::cout << "incorrecto" << std::endl;
    }
    i++;
  }
  std::cout << "suma " << suma << std::endl;
}
