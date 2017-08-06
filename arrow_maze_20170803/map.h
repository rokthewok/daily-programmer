#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "coordinate.h"


namespace rokthewok {

class Map {
public:
  struct Direction {
    static const std::string N;
    static const std::string S;
    static const std::string E;
    static const std::string W;
    static const std::string NW;
    static const std::string NE;
    static const std::string SW;
    static const std::string SE;
    static const std::string NONE;
    static const std::string HOME;
  };

  Map(int rows, int columns);
  Map(const Map & other);
  Map & operator=(const Map & rhs);
  virtual ~Map();
  void set(int row, int column, const std::string & direction);
  const std::string & get(int row, int column) const;
  void setRow(int row, const std::vector<std::string> & directions);
  std::vector<Coordinate> findPathHome(const Coordinate & start) const;
  void print(std::ostream & out) const;
private:
  bool inRange(int row, int column) const;
  void allocate(int rows, int columns);
  void deallocate();
  static bool isValidDirection(const std::string & direction);

  int d_rows;
  int d_columns;
  std::string ** d_map;

  static const std::unordered_set<std::string> DIRECTIONS;
  static const std::unordered_map<std::string, Coordinate> MOVEMENT;
};

} // namespace rokthewok

std::ostream & operator<<(std::ostream & out, const rokthewok::Map & map);

