#include <iostream>
#include <cstdlib> // rand

#include "grid.h"
#include "maze_presenters.h"
#include "generators/generator.h"
#include "generators/wilson.h"

using namespace std;

const int seed = 0xDECAF1;


int main() {
  srand(seed);

  int width = 50, height = 50;

  Generator* b = new Wilson();
  Grid* grid = b->generate(width, height);

  MazePresenters::stdout(grid);

  return 0;
}
