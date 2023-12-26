#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
const int in_windows = 1;
#else
const int in_windows = 0;
#endif

#define LETTERS_LN 26
#define COLPAIRS_LN 7
#define ARG_CNT 1

const char letters[LETTERS_LN] = {
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'o', 'p', 'a', 's', 'd', 'f',
    'g', 'h', 'j', 'k', 'l', 'i', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
}; // I could also just write all them in ""s like a string. Dummy

int main(int argc, char *argv[]) {
  const unsigned int time_opt = 3000000; // in nanoseconds

  // the main program
  initscr();
  noecho();

  srand(time(NULL));

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  } else if (in_windows) {
    endwin();
    printf("Asd does not support windows YET, sorry!\n");
    exit(0);
  }

  start_color();

  const int col_pairs[COLPAIRS_LN] = {
      init_pair(1, COLOR_RED, COLOR_BLACK),
      init_pair(2, COLOR_GREEN, COLOR_BLACK),
      init_pair(3, COLOR_BLUE, COLOR_BLACK),
      init_pair(4, COLOR_CYAN, COLOR_BLACK),
      init_pair(5, COLOR_YELLOW, COLOR_BLACK),
      init_pair(6, COLOR_WHITE, COLOR_BLACK),
      init_pair(7, COLOR_MAGENTA, COLOR_BLACK),
  };

  const unsigned int count =
      rand() % 2000 + 1000; // how many letters will appear
  for (unsigned int i = 0; i < count; ++i) {
    int col_attr = COLOR_PAIR(rand() % COLPAIRS_LN);
    attron(col_attr);

    // NOTE: AI helped this timing part
    struct timespec sleep_dur = {
        .tv_sec = 0, .tv_nsec = time_opt}; // tv stands for time value
    nanosleep(&sleep_dur,
              NULL); // nanosleep does not rely on the pc specs, I hope so
    // ENDNOTE

    printw("%c", letters[rand() % LETTERS_LN]);
    refresh();
    attroff(col_attr);
  }

  printw(
      "\n\nThe joy came to an end :( I mean you can restart it if you want :)");
  refresh();
  getch();

  endwin();

  return 0;
}
