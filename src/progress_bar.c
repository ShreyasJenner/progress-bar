/* Program file to implement a progress bar 
 * Must be called after the file providing the data for progess bar is started
 */

#include <unistd.h>
#include <ncurses.h>

#include "../include/progress_bar.h"


/*
 * function maps the passed integer into a value between 0 and term_width 
 */
int map_into_range(int val, int term_width, int data_max) {
    return (val*term_width)/data_max;
}

/*
 * Function draws a progress bar onto the screen
 * Assumes that curses window has been initialized with the required settings
 * Prints the progress bar on the line passed as arg
 * Prints the value onto the next line
 */
void progress_bar(int data_cur_val, int data_max_val, int print_liney) {
    mvprintw(print_liney, 
            map_into_range(data_cur_val, getmaxx(stdscr), data_max_val),
            "\u2593");
    mvprintw(print_liney+1, 0, "%d", data_cur_val); 
    refresh();
}
