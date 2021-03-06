#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define PRINT_S32_ARR(arr, len) \
        printf("[ "); \
        for(int32_t i=0; i<(len); i++) \
          printf("%d, ", arr[i]);\
        printf("]\n");

#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

/** 
* In a sorted array, find the number of elements strictly smaller than the key
* Should handle duplicates properly
*/
int32_t rank(int32_t arr[], int32_t key, int32_t st, int32_t end)
{
  if(arr == NULL) return 0; // ideally need to compare only once. But removing the intermediary function and directly accessing recursive function.

  if(end < st) return 0;

  int32_t mid = (st + end)/2;

  if(arr[mid] >= key)
  {
    if(mid == st) return mid; // beginning of subarray (could have duplicates), return mid.
    if(arr[mid-1] < key) return mid; // arr[mid] is first element >= key, return mid.
    /** arr[mid] must be one of the duplicates and recurse over st -- mid-1 to find the beginning idx of key */
    return rank(arr, key, st, mid-1);
  }
  else // arr[mid] < key
  {
    if(mid == end) return mid+1; // last element of subarray is < key. so "end"+1 (incl the end element) number of elements are < key
    return rank(arr, key, mid+1, end);
  }

}

/** comparator used in qsort */
int32_t int_compare_asc(const void *e1, const void *e2)
{
  int32_t e1_int = *((int32_t*)e1);
  int32_t e2_int = *((int32_t*)e2);
  return e1_int - e2_int;
}


static void test_rank(int32_t arr[], int32_t len)
{
  if(arr == NULL) return;
  if(len == 0) return;

  qsort(arr, len, sizeof(arr[0]), int_compare_asc);
  PRINT_S32_ARR(arr, len);

  int32_t key;
  
  key = arr[0]-1;       printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));
  key = arr[len/4];     printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));
  key = arr[len/2];     printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));
  key = arr[len/2]+1;   printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));
  key = arr[3*len/4]+1; printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));
  key = arr[len-1]+1;   printf("input=%d, rank=%d\n", key, rank(arr, key, 0, len-1));

  puts("");
}


int main(void)
{
  int32_t arr0[] = {-1,1,3,5,2};        test_rank(arr0, ARR_LEN(arr0));
  int32_t arr1[] = {1,2,3,4,5,6};       test_rank(arr1, ARR_LEN(arr1));
  int32_t arr2[] = {-1,1,1,1,4,6,-1,2,2,2,2,5};       test_rank(arr2, ARR_LEN(arr2));

  return 0;
}