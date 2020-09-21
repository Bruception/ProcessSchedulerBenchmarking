#include <stdio.h>
#include "process.h"
#include "queue.h"

int main() {
  queue* test_queue = create_queue();
  process* test_process = create_process(0, 10, 20);
  process* test_process2 = create_process(0, 20, 30);
  print_queue(test_queue);
  add_to_queue(test_queue, test_process);
  add_to_queue(test_queue, test_process2);
  print_queue(test_queue);
  remove_from_queue(test_queue);
  print_queue(test_queue);
  remove_from_queue(test_queue);
  print_queue(test_queue);
  add_to_queue(test_queue, test_process2);
  add_to_queue(test_queue, test_process);
  print_queue(test_queue);
  return 0;
}
