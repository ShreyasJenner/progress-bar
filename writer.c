/* Program file to implement writer code for writing into shared memory buffer
 * Must be called after the progess bar executable is started
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct dimensions {
    int data_cur_val;
    int data_max_val;
    // indicates if data has started being updated
    int start;
};

int main() {
    key_t key;
    int shmid, i;
    struct dimensions *dm;

    // generate a key
    key = ftok("progress_bar.c", 100);
    if(key==-1) {
        perror("using ftok");
        exit(1);
    }

    // get shmid
    shmid = shmget(key, sizeof(struct dimensions), 0666|IPC_CREAT);
    if(shmid<0) {
        perror("Calling shmget");
        exit(1);
    }

    // attach shared memory
    dm = (struct dimensions*)shmat(shmid, 0, 0);
    if(dm==(void *)-1) {
        perror("Attaching shared memory buffer");
        exit(1);
    }

    // write into shared buffer
    dm->data_cur_val = 0;
    dm->data_max_val = 125;
    
    // set start to 1 to signal progress bar to start
    dm->start = 1;

    // modify data in shared memory buffer
    for(i=0;i<125;i++) {
        dm->data_cur_val = i;
        // delay for 100msec
        usleep(100*1000);
    }

    // detach shared memory
    shmdt(dm);

    return 0;
}
