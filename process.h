#include "queue.h"

#ifndef PROCESS_H
#define PROCESS_H

typedef struct interval_struct {
  int start;
  int end;
} interval;

typedef struct process_struct {
  int priority;
  int burst_time;
  int arrival_time;
  int start_time;
  int end_time;
  int id;
  queue* intervals;
} process;

process* create_process(int id, int priority, int burst_time, int arrival_time);

#endif
