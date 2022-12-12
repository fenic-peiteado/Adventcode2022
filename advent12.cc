#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

// Advent of code 12
// Encontra el camino mas corto entre dos punto
// El punto S y el punto E  solo se puede mover a punto adyacentes
//  Moviento en diagonal no es valido
std::vector<std::vector<char>> map_a_z;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<std::pair<int, int>>> parent;
// Moviento U,D,L,R
bool is_minor(std::pair<int, int> current, std::pair<int, int> next) {
  int current_height = map_a_z[current.first][current.second];
  int next_height = map_a_z[next.first][next.second];
  if (abs(current_height - next_height) <= 1 || current_height >= next_height) {
    return true;
  }
  return false;
}

bool is_valid_move(std::pair<int, int> current, std::pair<int, int> next) {
  if (next.first >= 0 && next.first < map_a_z.size() && next.second >= 0 &&
      next.second < map_a_z[next.first].size() &&
      !visited[next.first][next.second]) 
      {
    if (is_minor(current, next)) {
      return true;
    }
  }
  return false;
}
std::map<char, std::pair<int, int>> moves = {
    {'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};
// Mapa esta rellenado "a" la "z" representando siendo cada uno una altura
// La a es la elevacion mas baja y la z es la mas alta
// y no puede saltar mas de 1 altura ejemplo a->b es valido pero a->c no es
// valido
int main() {
  std::ifstream file("prueba");
  std::string line;
  while (std::getline(file, line)) {
    std::vector<char> row_a;
    std::vector<bool> row_b;
    std::vector<std::pair<int, int>> row_c;
    for (auto c : line) {
      row_a.push_back(c);
      row_b.push_back(false);
      row_c.push_back({0, 0});
    }
    map_a_z.push_back(row_a);
    visited.push_back(row_b);
    parent.push_back(row_c);
  }

  // Encontra el nodo inicial S
  // Encontra el nodo final E
  std::pair<int, int> start;
  std::pair<int, int> end;
  for (size_t i = 0; i < map_a_z.size(); i++) {
    for (size_t j = 0; j < map_a_z[i].size(); j++) {
      if (map_a_z[i][j] == 'S') {
        start = {i, j};
      } else if (map_a_z[i][j] == 'E') {
        end = {i, j};
      }
    }
  }
  // BFS
  // 1. Crear una cola
  std::queue<std::pair<int, int>> q;
  // 2. Agregar el nodo inicial a la cola
  q.push(start);
  // 3. Mientras la cola no este vacia
  while (!q.empty()) {
    // 4. Sacar el primer elemento de la cola
    auto current = q.front();
    q.pop();
    // 5. Si el elemento es el nodo objetivo terminar
    if (current == end) {
        std::cout << "Encontrado" << std::endl;
        std::cout << current.first << " " << current.second << std::endl;
      return 0;
    }
    // 6. Si no es el nodo objetivo agregar todos los nodos adyacentes a la cola
    for (auto move : moves) {
      auto next = current;
      next.first += move.second.first;
      next.second += move.second.second;
      // 7. Repetir desde el paso 3
      if (next.first >= 0 && next.first < map_a_z.size() && next.second >= 0 &&
          next.second < map_a_z[next.first].size() &&
          !visited[next.first][next.second] && is_valid_move(current, next)) {
        q.push(next);
        visited[next.first][next.second] = true;
        parent[next.first][next.second] = current;
      }
    }
  }
    // Imprimir el numero de movimientos para llegar al nodo objetivo
    std::cout << "Numero de movimientos: " << std::endl;
    std::cout << parent[end.first][end.second].first << " " << parent[end.first][end.second].second << std::endl;


  return 0;
}
