#include <stdio.h>
#include "process.h"
#include "heap.h"
#include "queue.h"

int compare_priority(process* p1, process* p2) {
  return p1->priority - p2->priority;
}

int compare_burst_time(process* p1, process* p2) {
  return p1->burst_time - p2->burst_time;
}

int main() {
  heap* test_heap = create_heap(100, &compare_priority);
  heap* test_heap2 = create_heap(100, &compare_burst_time);
  process* p1 = create_process(-2, 8, 0);
  process* p2 = create_process(-1, 5, 5);
  process* p3 = create_process(-3, 2, 8);
  printf("P1: %p, P2: %p, P3: %p\n", p1, p2, p3);
  printf("Priority Based Comparison:\n");
  add_to_heap(test_heap, p1);
  add_to_heap(test_heap, p2);
  add_to_heap(test_heap, p3);
  print_heap(test_heap);
  printf("Top: %p\n", remove_min_from_heap(test_heap));
  printf("Top: %p\n", remove_min_from_heap(test_heap));
  printf("Top: %p\n", remove_min_from_heap(test_heap));
  printf("Burst Time Based Comparison:\n");
  add_to_heap(test_heap2, p1);
  add_to_heap(test_heap2, p2);
  add_to_heap(test_heap2, p3);
  print_heap(test_heap2);
  printf("Top: %p\n", remove_min_from_heap(test_heap2));
  printf("Top: %p\n", remove_min_from_heap(test_heap2));
  printf("Top: %p\n", remove_min_from_heap(test_heap2));
  return 0;
}
