#pragma once

#include "coords.h"

class Grid {
  public:
    int width;
    int height;
    Grid(int, int);

    Direction at(int, int);
    void setAt(int, int, Direction);
    void orAt(int, int, Direction);

  private:
    Coord* grid;
    int coord(int, int);
};
