#include <stdio.h>
#include <stdint.h>
#include <math.h> // use pow()

uint32_t nth_magic_number(uint32_t n)
{
  int32_t idx = 1;
  uint32_t acc = 0;
  while(n != 0)
  {
    if(n & 0x1) acc += pow(5, idx);
    idx += 1;
    n >>= 1;
  }

  return acc;
}
static void run_test(uint32_t n)
{
  printf("n = %d, nth magic number = %d\n\n", n, nth_magic_number(n));
}
int main(void)
{
  run_test(1);
  run_test(2);
  run_test(3);
  run_test(4);
  run_test(10);
  return 0;
}