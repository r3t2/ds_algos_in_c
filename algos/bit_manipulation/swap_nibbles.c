#include <stdio.h>
#include <stdint.h>

#define UPPER_NIBBLE_MASK_64 0xF0F0F0F0F0F0F0F0ULL
#define LOWER_NIBBLE_MASK_64 0x0F0F0F0F0F0F0F0FULL
#define SWAP_NIBBLES_64(x) ((UPPER_NIBBLE_MASK_64 & (x))>>4) | \
                           ((LOWER_NIBBLE_MASK_64 & (x))<<4)
                           

uint64_t swap_nibbles_64(uint64_t);

uint64_t inline swap_nibbles_64(const uint64_t in)
{
  uint64_t upper_nibbles = in & UPPER_NIBBLE_MASK_64;
  uint64_t lower_nibbles = in & LOWER_NIBBLE_MASK_64;
  return (upper_nibbles >> 4) | (lower_nibbles << 4);
}

static void run_test(const uint64_t in)
{
  uint64_t ret_value = swap_nibbles_64(in);
  uint64_t ret_value_macro = SWAP_NIBBLES_64(in);
  printf("input=%016llx, output=%016llx, macro output=%016llx\n", in, ret_value, ret_value_macro);
}

int main(void)
{
  run_test(0xABCD);
  run_test(UPPER_NIBBLE_MASK_64);
  run_test(LOWER_NIBBLE_MASK_64);
  run_test(-1ULL);

  return 0;
}