#include <stdlib.h>
#include <stdio.h>

#include "schedulers.h"
#include "heap.h"
#include "queue.h"

int compare_priority(process* p1, process* p2) {
  return p1->priority - p2->priority;
}

int compare_burst_time(process* p1, process* p2) {
  return p1->burst_time - p2->burst_time;
}

int compare_arrival_time(process* p1, process* p2) {
  return p1->arrival_time - p2->arrival_time;
}

int compare_arrival_time_and_burst_time(process* p1, process* p2) {
  return (p1->burst_time == p2->burst_time)
    ? compare_arrival_time(p1, p2)
    : compare_burst_time(p1, p2);
}

// Wait Time = Turnaround time - burst time
// Turnaround time = completion time - arrival time
// Response time = start_time - arrival_time
double get_average_wait_time(process** processes, int capacity) {
  double average_wait_time = 0;
  int turnaround_time;
  for (int i = 0; i < capacity; ++i) {
    turnaround_time = processes[i]->end_time - processes[i]->arrival_time;
    average_wait_time += turnaround_time - processes[i]->burst_time;
  }
  return average_wait_time / capacity;
}

void reset_processes(process** processes, int capacity) {
  for (int i = 0; i < capacity; ++i) {
    processes[i]->start_time = 0;
    processes[i]->end_time = 0;
  }
}

double get_utilization(int cpu_time, int idle_time) {
  return 100 - (((double)idle_time / cpu_time) * 100);
}

heap* get_process_heap(process** processes, int capacity, int (*compare)(process* p1, process* p2)) {
  heap* arrival_time_pq = create_heap(capacity, compare);
  for (int i = 0; i < capacity; ++i) {
    add_to_heap(arrival_time_pq, processes[i]);
  }
  return arrival_time_pq;
}

void first_come_first_serve(process** processes, int capacity) {
  int current_time = 0;
  int idle_time = 0;
  double average_turnaround_time = 0;
  heap* arrival_time_pq = get_process_heap(processes, capacity, &compare_arrival_time);
  while (arrival_time_pq->size > 0) {
    int next_min_arrival_time = get_min_from_heap(arrival_time_pq)->arrival_time;
    if (current_time < next_min_arrival_time) {
        int difference = next_min_arrival_time - current_time;
        idle_time += difference;
        current_time += difference;
    }
    process* current_process = remove_min_from_heap(arrival_time_pq);
    current_process->start_time = current_time;
    printf("Process with id: %d is running...\n", current_process->id);
    current_time += current_process->burst_time;
    current_process->end_time = current_time;
    int turnaround_time = current_time - current_process->arrival_time;
    average_turnaround_time += turnaround_time;
    printf("\tTurnaround time for Process with id: %d : %d\n", current_process->id, turnaround_time);
  }
  average_turnaround_time /= capacity;
  printf("Average turnaround time: %.2f\n", average_turnaround_time);
  printf("Average wait time: %.2f\n", get_average_wait_time(processes, capacity));
  printf("CPU Utilization: %.2f%%\n", get_utilization(current_time, idle_time));
  reset_processes(processes, capacity);
}

void shortest_job_first(process** processes, int capacity) {
  int current_time = 0;
  int idle_time = 0;
  double average_turnaround_time = 0;
  heap* arrival_time_pq = get_process_heap(processes, capacity, &compare_arrival_time);
  heap* burst_time_pq = create_heap(capacity, &compare_burst_time);
  while (arrival_time_pq->size > 0 || burst_time_pq->size > 0) {
    if (arrival_time_pq->size > 0) {
      int next_min_arrival_time = get_min_from_heap(arrival_time_pq)->arrival_time;
      if (current_time < next_min_arrival_time && burst_time_pq->size == 0) {
        int difference = next_min_arrival_time - current_time;
        idle_time += difference;
        current_time += difference;
      }
    }
    while (
      arrival_time_pq->size > 0
      && get_min_from_heap(arrival_time_pq)->arrival_time <= current_time
    ) {
      add_to_heap(burst_time_pq, remove_min_from_heap(arrival_time_pq));
    }
    process* current_process = remove_min_from_heap(burst_time_pq);
    current_process->start_time = current_time;
    printf("Process with id: %d is running...\n", current_process->id);
    current_time += current_process->burst_time;
    current_process->end_time = current_time;
    int turnaround_time = current_time - current_process->arrival_time;
    average_turnaround_time += turnaround_time;
    printf("\tTurnaround time for Process with id: %d : %d\n", current_process->id, turnaround_time);
  }
  average_turnaround_time /= capacity;
  printf("Average turnaround time: %.2f\n", average_turnaround_time);
  printf("Average wait time: %.2f\n", get_average_wait_time(processes, capacity));
  printf("CPU Utilization: %.2f%%\n", get_utilization(current_time, idle_time));
  reset_processes(processes, capacity);
}

void round_robin(process** processes, int capacity, int time_quanta) {

}

void preemptive_priority(process** processes, int capacity) {
}

void preemptive_shortest_job_first(process** processes, int capacity) {
  
}
