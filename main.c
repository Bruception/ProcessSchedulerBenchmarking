#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "schedulers.h"

int main() {
  process** processes = (process**)malloc(sizeof(process*) * 5);
  processes[0] = create_process(1, 0, 8, 0);
  processes[1] = create_process(2, 0, 5, 3);
  processes[2] = create_process(3, 0, 10, 4);
  processes[3] = create_process(4, 0, 9, 6);
  processes[4] = create_process(5, 0, 7, 11);
  first_come_first_serve(processes, 5);
  shortest_job_first(processes, 5);
  return 0;
}
