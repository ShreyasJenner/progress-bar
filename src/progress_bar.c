/* Program file to implement a progress bar 
 * Must be called after the file providing the data for progess bar is started
 */

#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/shm.h>

#include "../include/struct.h"
#include "../include/progress_bar.h"


// function maps the value given into a value between 0 and term_width 
int map_into_range(int val, int term_width, int data_max) {
    return (val*term_width)/data_max;
}

// function to draw progress bar in screen
void* progress_bar(void *args) {
    key_t key;
    int shmid, term_itr, term_width, i;
    struct dimensions *dm;

    // initalize ncurses
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    // initalize term vars
    term_itr=0;
    term_width = getmaxx(stdscr);

    // set key value
    key = (key_t)1234;

    shmid = shmget(key, sizeof(struct dimensions), 0666|IPC_CREAT);
    if(shmid<0) {
        return (void *)-1;
    }

    // attach shared memory
    dm = (struct dimensions*)shmat(shmid, NULL, 0);
    if(dm==(void *)-1) {
        return (void *)-1;
    }
    
    // set start to 0 to indicate data hasnt started being updated
    dm->start = 0;

    // wait till start is changed to 1
    while(dm->start==0) {;}


    // while loop to print the progress bar on the screen
    while(term_itr<term_width-1) {
        if(wgetch(stdscr)==KEY_RESIZE) {
            term_width = getmaxx(stdscr);
            clear();

            for(i=0;i<term_itr;i++) {
                wprintw(stdscr, "\u2593");
            }
            refresh();
        }


        // wait in the while loop for data value to increase
        while(term_itr>map_into_range(dm->data_cur_val, term_width, dm->data_max_val)) {
        }
        wprintw(stdscr, "\u2593"); 
        refresh();
        term_itr++;
    }

    // detach and destroy shared memory 
    shmdt(dm);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
