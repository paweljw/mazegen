#include <iostream>
#include <cstdlib> // rand
#include <curses.h>

#include "grid.h"
#include "maze_presenters.h"
#include "generators/generator.h"
#include "generators/wilson.h"

using namespace std;

int main(int argc, char** argv) {
  srand(time(0));

  // TODO: Surprise! Crashes on non-square mazes!
  int width = 40, height = 40;

  Generator* b = new Wilson();
  Grid* grid = b->generate(width, height);

  MazePresenters::ncurses(grid);

  return 0;
}
