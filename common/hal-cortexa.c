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

#ifdef __aarch64__
uint64_t hal_get_time()
{
  uint64_t t;
  asm volatile("mrs %0, PMCCNTR_EL0":"=r"(t));
  return t;
}
#else

uint64_t hal_get_time()
{
  // TODO: this is actually a 32-bit counter, so it won't work for very long running schemes
  //       need to figure out a way to get a 64-bit cycle counter
  unsigned cc;
  asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cc));
  return cc;
}
#endif


size_t hal_get_stack_size(void)
{
  return 0;
}
