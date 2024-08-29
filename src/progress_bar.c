/* Program file to implement a progress bar 
 * Must be called after the file providing the data for progess bar is started
 */

#include <unistd.h>
#include <ncurses.h>

#include "../include/progress_bar.h"


// function maps the value given into a value between 0 and term_width 
int map_into_range(int val, int term_width, int data_max) {
    return (val*term_width)/(double)data_max;
}

// function to draw progress bar in screen
void progress_bar(int data_cur_val, int data_max_val, int resize) {
    int term_width, i, x, y;

    // initalize term vars
    i = 0;
    term_width = getmaxx(stdscr);
    
    curs_set(0);
    // clear line and print bar from beginning if terminal has been resizee
    if(resize) {
        clrtoeol();
        // if term itr is less than mapped value and term max size
        while(i<=map_into_range(data_cur_val, term_width, data_max_val)) {
            printw("\u2593");
            i++;
        }
    } else {
        printw("\u2593");
    }
    refresh();
    curs_set(1);
}
