/* 
 * Program file to implement a progress bar 
 * Uses ncurses and unicode characters to print the progress bar
 * Functions in this program call refresh by themselves
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
 * The value is printed first, as the cursor location is used to determine if
 * there are line breaks in the progress bar
 * Cursor location needs to be at the last progress bar print location
 */
void progress_bar(int data_cur_val, int data_max_val, int print_y) {
    /* Declaration */
    int x,y,print_loc;

    /* store current position of cursor */
    getyx(stdscr, y, x);


    /* print the value */
    mvprintw(print_y+1, 0, "%d", data_cur_val); 
    
    /* 
     * Get the print_loc value. If it is not x+1, then print characters till 
     * the print_loc value is reached
     */
    print_loc = map_into_range(data_cur_val, getmaxx(stdscr), data_max_val);
    while(x<=print_loc) {
        mvprintw(print_y, x, "\u2593");
        x++;
    }
    refresh();
}


/*
 * Function to be called when the terminal has been resized
 * Will get the value for the current terminal width and reprint the progress bar on the same line
 * Cursor final position is at the last printing loaction of progress bar
 */
void reprint_pb(int data_cur_val, int data_max_val, int print_y) {
    /* Declaration */
    int i, max_x_pos;

    /* 
     * move to line containing the value 
     * clear that line and reprint it 
     */
    move(print_y+1, 0);
    clrtoeol();
    mvprintw(print_y+1, 0, "%d", data_cur_val); 


    /* 
     * move to line containing the progress bar 
     * clear that line and reprint the progress bar 
     */
    move(print_y, 0);
    clrtoeol();
    max_x_pos = map_into_range(data_cur_val, getmaxx(stdscr), data_max_val);   
    for(i=0;i<max_x_pos;i++) {
        mvprintw(print_y, i, "%s", "\u2593"); 
    }

    refresh();
}
