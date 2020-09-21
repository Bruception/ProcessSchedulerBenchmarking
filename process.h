#ifndef PROCESS_H
#define PROCESS_H

typedef struct process_struct {
  int priority;
  int burst_time;
  int arrival_time;
} process;

process* create_process(int priority, int burst_time, int arrival_time);

#endif
