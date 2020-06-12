#include <iostream>
#include <cstdlib> // rand
#include <vector>
#include <bits/stdc++.h>

#include "maze.h"
using namespace std;

const ushort WIDTH = 50;
const ushort HEIGHT = 50;

const int seed = 0xDECAF1;

ushort coord(Coord x, Coord y) {
  return x * WIDTH + y;
}

void display_maze(ushort* grid, ushort cx, ushort cy) {
  cout << "\e[2J\e[H";

  // top frame
  cout << " ";
  for(ushort i = 0; i < WIDTH * 2 - 1; i++) {
    cout << "_";
  }
  cout << endl;

  for(ushort y = 0; y < HEIGHT; y++) {
    cout << "|";
    for(ushort x = 0; x < WIDTH; x++) {
      Coord cell = grid[coord(x, y)];

      if(cx == x && cy == y) {
        cout << "\e[43m";
      }

      if(cell == 0 && y+1 < HEIGHT && grid[coord(x, y+1)] == 0) {
        cout << " ";
      } else {
        if((cell & S) != 0) {
          cout << " ";
        } else {
          cout << "_";
        }
      }

      if(cx == x && cy == y) {
        cout << "\e[0m";
      }

      if (cell == 0 && x+1 < WIDTH && grid[coord(x+1, y)] == 0) {
        if(y+1 < HEIGHT && (grid[coord(x, y+1) == 0 || grid[coord(x+1, y+1)] == 0])) {
          cout << " ";
        } else {
          cout << "_";
        }
      } else if ((cell & E) != 0) {
        if(((cell | grid[coord(x+1, y)]) & S) != 0) {
          cout << " ";
        } else {
          cout << "_";
        }
      } else {
        cout << "|";
      }
    }
    cout << endl;
  }
}
vector<CoordDirection> walk(ushort* grid) {
  vector<Direction> directions = {N, S, E, W};

  do {
    Coord cx = rand() % WIDTH;
    Coord cy = rand() % HEIGHT;

    if(grid[coord(cx, cy)] != 0) continue;

    short* visits = new short[WIDTH * HEIGHT];

    for(ushort i = 0; i < WIDTH * HEIGHT; i++) {
      visits[i] = -1;
    }

    Coord start_x = cx, start_y = cy;

    bool walking = true;

    while(walking) {
      display_maze(grid, cx, cy);
      walking = false;
      random_shuffle(directions.begin(), directions.end());

      for(ushort k = 0; k < 4; k++) {
        Direction dir = directions[k];
        Coord nx = cx + DX.at(dir);
        Coord ny = cy + DY.at(dir);

        if(nx >= 0 && ny >= 0 && nx < WIDTH && ny < HEIGHT) {
          visits[coord(cx, cy)] = dir;

          if (grid[coord(nx, ny)] != 0) {
            k = 5; // break
          } else {
            cx = nx;
            cy = ny;
            walking = true;
            k = 5; // break
          }
        }
      }
    }
    vector<CoordDirection> path;
    Coord x = start_x, y = start_y;

    do {
      short dir = visits[coord(x, y)];
      if(dir == -1) break;

      path.push_back(make_tuple(x, y, dir));
      x = x + DX.at(dir);
      y = y + DY.at(dir);
    } while(true);

    return path;
  } while(true);
}


int main() {
  srand(seed);
  cout << "Hello world" << endl;

  ushort* grid = new ushort[WIDTH * HEIGHT];

  for(ushort i = 0; i < WIDTH*HEIGHT; i++) {
    grid[i] = 0;
  }

  grid[coord(rand() % WIDTH, rand() % HEIGHT)] = IN;

  ushort remaining = WIDTH * HEIGHT - 1;

  while(remaining > 0) {
    vector<CoordDirection> path = walk(grid);

    for (vector<CoordDirection>::iterator it = path.begin() ; it != path.end(); ++it) {
      Coord x = get<0>(*it);
      Coord y = get<1>(*it);
      Direction dir = get<2>(*it);

      Coord nx = x + DX.at(dir), ny = y + DY.at(dir);

      grid[coord(x, y)] |= dir;
      grid[coord(nx, ny)] |= OPPOSITE.at(dir);

      remaining--;

      display_maze(grid, -1, -1);
    }
  }

  display_maze(grid, -1, -1);

  return 0;
}
