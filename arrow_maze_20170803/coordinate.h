#pragma once

#include <string>
#include <iostream>


namespace rokthewok {

class Coordinate {
public:
  Coordinate();
  Coordinate(int row, int column);
  Coordinate(const Coordinate & other);
  Coordinate & operator=(const Coordinate & rhs);
  ~Coordinate();
  static Coordinate fromString(const std::string & c);
  int row() const;
  int column() const;
  void row(int row);
  void column(int column);
  void print(std::ostream & out) const;
private:
  int d_row;
  int d_column;
};

} // namespace rokthewok

std::ostream & operator<<(std::ostream & out,
                          const rokthewok::Coordinate & coordinate);
rokthewok::Coordinate operator+(const rokthewok::Coordinate & lhs,
                                const rokthewok::Coordinate & rhs);

