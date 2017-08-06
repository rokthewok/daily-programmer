/**
 * 08-03-2017: Challenge 325 - Arrow Maze
 *
 */
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include "map.h"
#include "coordinate.h"


std::vector<std::string> split(const std::string & input, char delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  while(start < input.size()) {
    size_t end = input.find(delimiter, start + 1);
    if(std::string::npos == end) {
      end = input.size();
    }
    std::string token(input.substr(start, end - start));
    if(!token.empty()) {
      tokens.push_back(token);
    }
    start = end + 1;
  }
  return tokens;
}

int main(int argc, char ** argv) {
  using namespace rokthewok;
  std::string coordinates;
  std::getline(std::cin, coordinates);
  Coordinate coordinate = Coordinate::fromString(coordinates);

  std::cout << coordinate << std::endl;

  std::vector<std::vector<std::string>> rows;
  std::string rawRow;
  while(std::getline(std::cin, rawRow)) {
    rows.push_back(split(rawRow, ' '));
    rawRow.clear();
  }

  Map map(rows.size(), rows[0].size());
  for(int i = 0; i < rows.size(); ++i) {
    map.setRow(i, rows[i]);
  }
  std::cout << map << std::endl;

  auto path = map.findPathHome(coordinate);
  for(auto p : path) {
    std::cout << p << std::endl;
  }

  return 0;
}

