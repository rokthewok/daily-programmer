#include "coordinate.h"
#include <regex>
#include <stdexcept>


namespace rokthewok {

Coordinate::Coordinate()
  : Coordinate::Coordinate(0, 0) {}

Coordinate::Coordinate(int row, int column)
  : d_row(row),
    d_column(column) {}

Coordinate::Coordinate(const Coordinate & other)
  : d_row(other.d_row),
    d_column(other.d_column) {}

Coordinate & Coordinate::operator=(const Coordinate & rhs) {
  if(this != &rhs) {
    d_row = rhs.d_row;
    d_column = rhs.d_column;
  }
  return *this;
}

Coordinate::~Coordinate() {}

Coordinate Coordinate::fromString(const std::string & c) {
  std::regex pattern("\\((\\d+), ?(\\d+)\\)");
  std::smatch results;
  if(!std::regex_match(c, results, pattern)) {
    throw std::invalid_argument("Bad coordinate string format");
  }

  int column = atoi(results[1].str().c_str());
  int row = atoi(results[2].str().c_str());

  return Coordinate(row, column);
}

int Coordinate::row() const {
  return d_row;
}

int Coordinate::column() const {
  return d_column;
}

void Coordinate::row(int row) {
  d_row = row;
}

void Coordinate::column(int column) {
  d_column = column;
}

void Coordinate::print(std::ostream & out) const {
  out << "(" << d_column << ", " << d_row << ")";
}

} // namespace rokthewok

std::ostream & operator<<(std::ostream & out,
                          const rokthewok::Coordinate & coordinate) {
  coordinate.print(out);
  return out;
}

rokthewok::Coordinate operator+(const rokthewok::Coordinate & lhs,
                                const rokthewok::Coordinate & rhs) {
  return rokthewok::Coordinate(lhs.row() + rhs.row(), lhs.column() + rhs.column());
}
