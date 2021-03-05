#include <stdio.h>
#include "hal.h"

void hal_setup(const enum clock_mode clock)
{
  (void) clock;
  //TODO figure out if we need to do someting here
}

void hal_send_str(const char* in)
{
  printf("%s\n", in);
}

uint64_t hal_get_time()
{
  uint64_t t;
  asm volatile("mrs %0, PMCCNTR_EL0":"=r"(t));
  return t;
}

size_t hal_get_stack_size(void)
{
  return 0;
}
