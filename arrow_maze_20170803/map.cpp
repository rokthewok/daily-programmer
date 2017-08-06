#include "map.h"
#include <stdexcept>
#include <iomanip>
#include <queue>


namespace rokthewok {

const std::string Map::Direction::N =    "n";
const std::string Map::Direction::S =    "s";
const std::string Map::Direction::E =    "e";
const std::string Map::Direction::W =    "w";
const std::string Map::Direction::NW =  "nw";
const std::string Map::Direction::NE =  "ne";
const std::string Map::Direction::SW =  "sw";
const std::string Map::Direction::SE =  "se";
const std::string Map::Direction::NONE = "-";
const std::string Map::Direction::HOME = "h";

const std::unordered_set<std::string> Map::DIRECTIONS = {
                                                 Map::Direction::N,
                                                 Map::Direction::S,
                                                 Map::Direction::E,
                                                 Map::Direction::W,
                                                 Map::Direction::NW,
                                                 Map::Direction::NE,
                                                 Map::Direction::SW,
                                                 Map::Direction::SE,
                                                 Map::Direction::NONE,
                                                 Map::Direction::HOME
                                               };
const std::unordered_map<std::string, Coordinate> Map::MOVEMENT = {
                                            {Map::Direction::N, Coordinate(-1, 0)},
                                            {Map::Direction::S, Coordinate(1, 0)},
                                            {Map::Direction::E, Coordinate(0, 1)},
                                            {Map::Direction::W, Coordinate(0, -1)},
                                            {Map::Direction::NW, Coordinate(-1, -1)},
                                            {Map::Direction::NE, Coordinate(-1, 1)},
                                            {Map::Direction::SW, Coordinate(1, -1)},
                                            {Map::Direction::SE, Coordinate(1, 1)},
                                            {Map::Direction::NONE, Coordinate(0, 0)},
                                            {Map::Direction::HOME, Coordinate(0, 0)}
                                          };

Map::Map(int rows, int columns)
  : d_rows(rows),
    d_columns(columns),
    d_map(NULL) {
  allocate(d_rows, d_columns);
}

Map::Map(const Map & other)
  : d_rows(other.d_rows),
    d_columns(other.d_columns),
    d_map(NULL) {
  allocate(d_rows, d_columns);
}

Map & Map::operator=(const Map & rhs) {
  if(this != &rhs) {
    d_rows = rhs.d_rows;
    d_columns = rhs.d_columns;
    deallocate();
    allocate(d_rows, d_columns);
  }
  return *this;
}

Map::~Map() {
  deallocate();
}

bool Map::inRange(int row, int column) const {
  return 0 <= row && d_rows > row && 0 <= column && d_columns > column;
}

void Map::allocate(int rows, int columns) {
  d_map = new std::string*[rows]();
  for(int i = 0; i < rows; ++i) {
    d_map[i] = new std::string[columns]();
  }
}

void Map::deallocate() {
  if(d_map) {
    for(int i = 0; i < d_rows; ++i) {
      delete [] d_map[i];
    }
    delete [] d_map;
  }
}

bool Map::isValidDirection(const std::string & direction) {
  return DIRECTIONS.end() != DIRECTIONS.find(direction);
}

void Map::set(int row, int column, const std::string & direction) {
  if(!inRange(row, column)) {
    throw std::out_of_range("Index out of range");
  }

  if(!isValidDirection(direction)) {
    throw std::invalid_argument("Bad direction argument");
  }
  d_map[row][column] = direction;
}

const std::string & Map::get(int row, int column) const {
  if(!inRange(row, column)) {
    throw std::out_of_range("Index out of range");
  }

  return d_map[row][column];
}

void Map::setRow(int row, const std::vector<std::string> & directions) {
  if(!inRange(row, 0)) {
    throw std::out_of_range("Index out of range");
  }
  for(int col = 0; col < d_columns; ++col) {
    if(!isValidDirection(directions.at(col))) {
      throw std::invalid_argument("Bad direction argument");
    }
    d_map[row][col] = directions.at(col);
  }
}

std::vector<Coordinate> Map::findPathHome(const Coordinate & start) const {
  if(!inRange(start.row(), start.column())) {
    throw std::out_of_range("Start coordinate is not in map");
  }

  std::queue<std::pair<Coordinate, std::vector<Coordinate>>> paths;
  Coordinate startMvmt(MOVEMENT.at(d_map[start.row()][start.column()]));
  auto startPath = std::make_pair(startMvmt, std::vector<Coordinate>(1, start));
  startPath.second.push_back(startMvmt + start);
  paths.push(startPath);

  while(!paths.empty()) {
    auto path = paths.front();
    paths.pop();

    // stopping condition
    if(Map::Direction::HOME == d_map[path.second.back().row()][path.second.back().column()]) {
      return path.second;
    }
    // two choices: move in the new direction, or continue in same direction as before

    // 1. move in new direction
    Coordinate movement = MOVEMENT.at(d_map[path.second.back().row()][path.second.back().column()]);
    auto newPath = path.second;
    newPath.push_back(path.second.back() + movement);
    paths.push(std::make_pair(movement, newPath));

    // 2. continue in current direction (if the direction is valid)
    Coordinate next = path.second.back() + path.first;
    if(inRange(next.row(), next.column())) {
      path.second.push_back(next);
      paths.push(path);
    }
  }
  return std::vector<Coordinate>();
}

void Map::print(std::ostream & out) const {
  for(int row = 0; row < d_rows; ++row) {
    for(int col = 0; col < d_columns; ++col) {
      out << std::setw(3) << std::right << d_map[row][col];
    }
    out << std::endl;
  }
}

} // namespace rokthewok

std::ostream & operator<<(std::ostream & out, const rokthewok::Map & map) {
  map.print(out);
  return out;
}

