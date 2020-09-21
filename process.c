#include <stdlib.h>
#include "process.h"

process* create_process(int id, int priority, int burst_time, int arrival_time) {
  process* new_process = (process*)malloc(sizeof(process));
  new_process->id = id;
  new_process->priority = priority;
  new_process->burst_time = burst_time;
  new_process->arrival_time = arrival_time;
  new_process->start_time = 0;
  new_process->end_time = 0;
  return new_process;
}
