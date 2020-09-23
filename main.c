#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "schedulers.h"

int main() {
  process** processes = (process**)malloc(sizeof(process*) * 5);
  processes[0] = create_process(1, 2, 1, 20);
  processes[1] = create_process(2, 1, 17, 3);
  processes[2] = create_process(3, 2, 12, 5);
  processes[3] = create_process(4, 2, 13, 1);
  processes[4] = create_process(5, 1, 4, 2);
  first_come_first_serve(processes, 5);
  shortest_job_first(processes, 5);
  round_robin(processes, 5, 5);
  preemptive_priority(processes, 5);
  preemptive_shortest_job_first(processes, 5);
  return 0;
}
