#include "grid.h"
#include "coords.h"

Grid::Grid(int width, int height): width(width), height(height) {
  grid = new Coord[width * height];

  for(auto i = 0; i < width * height; i++) grid[i] = 0;
}

Direction Grid::at(int x, int y) {
  return grid[coord(x, y)];
}

void Grid::setAt(int x, int y, Direction dir) {
  grid[coord(x, y)] = dir;
}

void Grid::orAt(int x, int y, Direction dir) {
  grid[coord(x, y)] |= dir;
}

int Grid::coord(int x, int y) {
  return y * height + x;
}

