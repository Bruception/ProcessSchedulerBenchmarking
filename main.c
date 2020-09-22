#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "schedulers.h"

int main() {
  process** processes = (process**)malloc(sizeof(process*) * 5);
  processes[0] = create_process(1, 2, 8, 0);
  processes[1] = create_process(2, 1, 3, 3);
  processes[2] = create_process(3, 2, 10, 4);
  processes[3] = create_process(4, 2, 9, 6);
  processes[4] = create_process(5, 1, 7, 8);
  first_come_first_serve(processes, 5);
  shortest_job_first(processes, 5);
  round_robin(processes, 5, 5);
  preemptive_priority(processes, 5);
  preemptive_shortest_job_first(processes, 5);
  return 0;
}
