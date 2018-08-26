#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PRINT_S32_ARR(arr, len) \
        printf("[ "); \
        for(int32_t i=0; i<(len); i++) \
          printf("%d, ", arr[i]);\
        printf("]\n");

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))


/** comparator used in qsort */
int32_t int_compare_asc(const void *e1, const void *e2)
{
  int32_t e1_int = *((int32_t*)e1);
  int32_t e2_int = *((int32_t*)e2);
  return e1_int - e2_int;
}

int32_t num_triplets_n2(int32_t arr[], int32_t len, int32_t target)
{
  /** First sort the array . Worst case O(N^2) qsort*/
  qsort(arr, len, sizeof(arr[0]), int_compare_asc);
  printf("sorted input = ");
  PRINT_S32_ARR(arr, len);

  int32_t num_triplets = 0;
  /** Consider one number at a time to be the first of the triplets*/
  for(int32_t i=0; i<len-2; i++)
  {
    int32_t j=i+1, k=len-1;
    while(j<k)
    {
      int32_t triplet_sum = arr[i] + arr[j] + arr[k];
      if(triplet_sum >= target) k--; // too large, try decreasing the last element (try -- because possible duplicates).
      else
      {
        int32_t num_pos_thirds = (k-j);
        num_triplets += num_pos_thirds;
        printf("i=%d, j=%d, k=%d\n", i, j, k);
        j++;
      }
    }
  }

  return num_triplets;
}



static void run_test(int32_t arr[], int32_t len, int32_t target)
{
  printf("input = ");
  PRINT_S32_ARR(arr, len);
  printf("target = %d\n", target);

  int32_t num_triplets = num_triplets_n2(arr, len, target);

  printf("num_triplets = %d\n\n", num_triplets);
}
int main(void)
{
  int32_t arr20[] = {-1,1,3,5,-2};        run_test(arr20, ARR_LEN(arr20), 0);
  int32_t arr21[] = {1,2,3,4,5,6};        run_test(arr21, ARR_LEN(arr21), 7);
  run_test(arr21, ARR_LEN(arr21), 100); //6C3 = 20 combinations

  return 0;
}