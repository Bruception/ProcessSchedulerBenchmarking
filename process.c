#include <stdlib.h>
#include "process.h"

process* create_process(int priority, int burst_time, int arrival_time) {
  process* new_process = (process*)malloc(sizeof(process));
  new_process->priority = priority;
  new_process->burst_time = burst_time;
  new_process->arrival_time = arrival_time;
  return new_process;
}
