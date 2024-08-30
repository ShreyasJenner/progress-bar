/*
 * Example program to show use of progress bar
 */

#include <unistd.h>
#include <ncurses.h>
#include <locale.h>

#include "../include/progress_bar.h"

int main() {
    int i;
    double term_itr;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    keypad(stdscr, true);
    nodelay(stdscr, true);

  
    term_itr = 0;
    // Loop that emulates changing data values
    for(i=0;i<125;i++) {
        mvprintw(0, 0, "%d\n", i); 

        // Pass the current data value to this function
        progress_bar(i, 125);

        // Sleep for a few milliseconds to allow the program to read the data from the buffer
        usleep(100*1000);
    }

    getch();
    endwin();
    return 0;
}
