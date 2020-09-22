#include "process.h"

#ifndef SCHEDULERS_H
#define SCHEDULERS_H

void first_come_first_serve(process** processes, int capacity);
void shortest_job_first(process** processes, int capacity);
void round_robin(process** processes, int capacity, int time_quanta);
void preemptive_priority(process** processes, int capacity);
void preemptive_shortest_job_first(process** processes, int capacity);

#endif