#include <stdlib.h>
#include "process.h"

process* create_process(int id, int arrival_time, int burst_time, int priority) {
  process* new_process = (process*)malloc(sizeof(process));
  new_process->id = id;
  new_process->priority = priority;
  new_process->burst_time = burst_time;
  new_process->arrival_time = arrival_time;
  // Indicate that the process hasn't been scheduled.
  new_process->start_time = -1;
  new_process->end_time = 0;
  new_process->intervals = create_queue();
  return new_process;
}
