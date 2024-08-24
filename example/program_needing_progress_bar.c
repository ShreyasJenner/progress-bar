/*
 * Program needs to be complied in following format
 * gcc <program_needing_progress_bar.c> src/progress_bar.c src/writer.c -lpthread
 */

#include <stdio.h>
#include <pthread.h>

#include "../headers/struct.h"
#include "../headers/writer.h"
#include "../headers/progress_bar.h"

int main() {
    int i;
    pthread_t thread_id;

    /* Pass the value that indicates completion of the progress bar to the init function 
     * It returns a pointer to a shared memory segment of the form struct dimensions
     */
    struct dimensions *dm = init(125);       /* example max value passed */


    /* Start the progress_bar function in a thread */
    pthread_create(&thread_id, NULL, progress_bar, NULL);
    
   
    /* Loop that emulates changing data values */
    for(i=0;i<125;i++) {
        /* Pass the current data value to this function */
        get_data(dm, i);
    }


    /* Call the finish functio to detach the shared memory */
    finish(dm);

    /* Clean the thread resources */
    pthread_join(thread_id, NULL);

    return 0;
}
