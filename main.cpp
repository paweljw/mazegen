#include <iostream>
#include <cstdlib> // rand
#include <vector>
#include <bits/stdc++.h>

#include "maze.h"
#include "grid.h"
using namespace std;

const int seed = 0xDECAF1;

void display_maze(Grid* grid) {
  // top frame
  cout << " ";
  for(auto i = 0; i < grid->width * 2 - 1; i++) {
    cout << "_";
  }
  cout << endl;

  for(auto y = 0; y < grid->height; y++) {
    cout << "|";
    for(auto x = 0; x < grid->width; x++) {
      Direction cell = grid->at(x, y);

      if(cell == 0 && y+1 < grid->height && grid->at(x, y+1) == 0) {
        cout << "X";
      } else {
        if((cell & S) != 0) {
          cout << " ";
        } else {
          cout << "_";
        }
      }

      if (cell == 0 && x+1 < grid->width && grid->at(x+1, y) == 0) {
        if(y+1 < grid->height && (grid->at(x, y+1) == 0 || grid->at(x+1, y+1) == 0)) {
          cout << "x";
        } else {
          cout << "_";
        }
      } else if ((cell & E) != 0) {
        if(((cell | grid->at(x+1, y)) & S) != 0) {
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

vector<CoordDirection> walk(Grid* grid) {
  vector<Direction> directions = {N, S, E, W};

  do {
    Coord cx = rand() % grid->width;
    Coord cy = rand() % grid->height;

    if(grid->at(cx, cy) != 0) continue;

    short* visits = new short[grid->width * grid->height];

    for(ushort i = 0; i < grid->width * grid->height; i++) {
      visits[i] = -1;
    }

    Coord start_x = cx, start_y = cy;

    bool walking = true;

    while(walking) {
      walking = false;
      random_shuffle(directions.begin(), directions.end());

      for(ushort k = 0; k < 4; k++) {
        Direction dir = directions[k];
        Coord nx = cx + DX.at(dir);
        Coord ny = cy + DY.at(dir);

        if(nx >= 0 && ny >= 0 && nx < grid->width && ny < grid->height) {
          visits[cx * grid->width + cy] = dir;

          if (grid->at(nx, ny) != 0) {
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
      short dir = visits[x * grid->width + y];
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

  int width = 50, height = 50;

  Grid *grid = new Grid(width, height);

  grid->setAt(rand() % width, rand() % height, IN);

  ushort remaining = width * height - 1;

  while(remaining > 0) {
    vector<CoordDirection> path = walk(grid);

    for (vector<CoordDirection>::iterator it = path.begin() ; it != path.end(); ++it) {
      Coord x = get<0>(*it);
      Coord y = get<1>(*it);
      Direction dir = get<2>(*it);

      Coord nx = x + DX.at(dir), ny = y + DY.at(dir);

      grid->orAt(x, y, dir);
      grid->orAt(nx, ny, OPPOSITE.at(dir));

      remaining--;
    }
  }

  display_maze(grid);

  return 0;
}
