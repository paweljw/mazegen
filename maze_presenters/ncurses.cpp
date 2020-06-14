#include <curses.h>

#include "../maze_presenters.h"

using namespace std;

void ncurses_preamble(void) {
  initscr();
  cbreak();
  noecho();
  clear();
}

// TODO: move to a proper menu system and stuff
void ncurses_temporary_wait_for_exit() {
  getch();
  endwin();
  exit(0);
}

void MazePresenters::ncurses(Grid* grid) {
  ncurses_preamble();

  // Top frame drawing
  mvaddch(0, 0, ' ');
  for(auto i = 0; i < grid->width * 2 - 1; i++) {
    mvaddch(0, i + 1, '_');
  }

  for(auto y = 0; y < grid->height; y++) {
    // left frame
    mvaddch(y + 1, 0, '|');
    for(auto x = 0; x < grid->width; x++) {
      Direction cell = grid->at(x, y);

      if((cell & S) != 0) {
        mvaddch(y + 1, x * 2 + 1, ' ');
      } else {
        mvaddch(y + 1, x * 2 + 1, '_');
      }

      if (cell == 0 && x+1 < grid->width && grid->at(x+1, y) == 0) {
        mvaddch(y + 1, x * 2 + 2, '_');
      } else if ((cell & E) != 0) {
        if(((cell | grid->at(x+1, y)) & S) != 0) {
          mvaddch(y + 1, x * 2 + 2, ' ');
        } else {
          mvaddch(y + 1, x * 2 + 2, '_');
        }
      } else {
        // right frame (x+1 > grid->width)
        mvaddch(y + 1, x * 2 + 2, '|');
      }
    }
  }

  mvaddstr(LINES - 1, 0, "Press any key to quit");
  refresh();

  ncurses_temporary_wait_for_exit();
}
