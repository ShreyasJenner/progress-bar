/*
 * Example program to show use of progress bar
 */

#include <unistd.h>
#include <ncurses.h>
#include <locale.h>

#include "../include/progress_bar.h"

int main() {
    int i;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    keypad(stdscr, true);
    curs_set(0);
    timeout(25);


    /* Loop to emulates changing data values */
    for(i=0;i<125;i++) {
        /* If terminal got resized, call this function */
        if(getch()==KEY_RESIZE) {
            reprint_pb(i,125,1);
        }

        /* Pass the current data value to this function */
        progress_bar(i, 125, 1);
    }

    getch();
    endwin();
    return 0;
}
