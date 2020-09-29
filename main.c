#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "schedulers.h"

int main() {
  FILE* fp = fopen("results.csv", "w+");
  process** processes = (process**)malloc(sizeof(process*) * 5);
  processes[0] = create_process(1, 0, 8, 4);
  processes[1] = create_process(2, 1, 6, 1);
  processes[2] = create_process(3, 2, 1, 2);
  processes[3] = create_process(4, 3, 9, 2);
  processes[4] = create_process(5, 5, 3, 3);
  first_come_first_serve(processes, 5, fp);
  shortest_job_first(processes, 5, fp);
  round_robin(processes, 5, 4, fp);
  preemptive_priority(processes, 5, fp);
  preemptive_shortest_job_first(processes, 5, fp);
  fclose(fp);
  return 0;
}
