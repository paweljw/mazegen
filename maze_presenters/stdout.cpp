#include <iostream>
#include "../maze_presenters.h"

using namespace std;

void MazePresenters::stdout(Grid* grid) {
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
