#include <iostream>
#include <cstdlib> // rand

#include "grid.h"
#include "maze_presenters.h"
#include "generators/generator.h"
#include "generators/wilson.h"

using namespace std;

int main(int argc, char** argv) {
  srand(time(0));

  int width = 50, height = 50;

  Generator* b = new Wilson();
  Grid* grid = b->generate(width, height);

  MazePresenters::stdout(grid);

  return 0;
}
