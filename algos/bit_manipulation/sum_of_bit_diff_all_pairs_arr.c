/**

Sum of bit differences among all pairs Given an integer array of n integers, find sum of bit
differences in all pairs that can be formed from array elements. Bit difference of a pair (x, y) is
count of different bits at same positions in binary representations of x and y.  For example, bit
difference for 2 and 7 is 2. Binary representation of 2 is 010 and 7 is 111 ( first and last bits
differ in two numbers).

Examples :

Input: arr[] = {1, 2}
Output: 4
All pairs in array are (1, 1), (1, 2)
                       (2, 1), (2, 2)
Sum of bit differences = 0 + 2 +
                         2 + 0
                      = 4

Input:  arr[] = {1, 3, 5}
Output: 8
All pairs in array are (1, 1), (1, 3), (1, 5)
                       (3, 1), (3, 3) (3, 5),
                       (5, 1), (5, 3), (5, 5)
Sum of bit differences =  0 + 1 + 1 +
                          1 + 0 + 2 +
                          1 + 2 + 0 
                       = 8
*/
#include <stdio.h>
#include <stdint.h>

#define SIZE_ARR(arr) (sizeof(arr)/sizeof(arr[0]))

/**
If the numbers come from a finite set, we can explore lookup table options.
*/
uint32_t num_set_bits(uint32_t x)
{
  uint32_t count = 0;
  while(x!=0)
  {
    count += 1;
    x &= (x-1);
  }

  return count;
}

uint32_t sum_of_bit_diffs(int32_t arr[], uint32_t len)
{
  uint32_t acc=0;
  for(uint32_t i=0; i<len; i++)
  {
    for(uint32_t j=i+1; j<len; j++)
    {
      acc += (num_set_bits(arr[i] ^ arr[j])*2);
    }
  }

  return acc;
}
static void run_test(int32_t arr[], uint32_t len)
{
  printf("num bit diffs = %d\n", sum_of_bit_diffs(arr, len));
}
int main(void)
{
  int32_t arr0[] = {1,2,3,4,5};
  run_test(arr0, SIZE_ARR(arr0));

  int32_t arr1[] = {1,2};
  run_test(arr1, SIZE_ARR(arr1));

  int32_t arr2[] = {1,3,5};
  run_test(arr2, SIZE_ARR(arr2));

  return 0;
}