#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

int map_into_range(int val, int term_width, int data_max);

void progress_bar(int data_cur_value, int data_max_value, int print_y);

void reprint_pb(int data_cur_val, int data_max_val, int print_y);

#endif
