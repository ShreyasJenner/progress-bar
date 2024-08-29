#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

int map_into_range(int val, int term_width, int data_max);

void progress_bar(int *term_itr, int data_cur_value, int data_max_value);

#endif
