#include<stdio.h>
#include<stdint.h>
#include<limits.h>


#define PRINT_S32_ARR(arr, len) \
        printf("[ "); \
        for(int32_t i=0; i<(len); i++) \
          printf("%d, ", arr[i]);\
        printf("]\n");

#define SIZE_ARR(arr) (sizeof(arr)/sizeof(arr[0]))



int32_t smallest_subarray(int32_t arr[], int32_t len, int32_t target)
{
  int32_t st=0, end=1;
  int32_t sum=arr[0];
  int32_t min_len = INT_MAX;

  while(end<len)
  {
    if((st < end) && (sum > target))
    {
      int32_t size = end-st;
      if(size < min_len)
      {
        min_len = size;
      }
      sum -= arr[st];
      st++;
    }
    else
    {
      sum += arr[end];
      end++;
    }
  }

  while(st<len)
  {
    if(sum > target)
    {
      int32_t size = end-st;
      if(size < min_len)
      {
        min_len = size;
      }
    }
    sum -= arr[st];    
    st++;
  }

  return (min_len<INT_MAX) * min_len;
}

static void run_test(int32_t arr[], int32_t len, int32_t target)
{
  printf("target = %d, input = ", target);
  PRINT_S32_ARR(arr, len);

  printf("smallest subarray size = %d\n\n", smallest_subarray(arr, len, target));
}

int main(void)
{
  int32_t target = 10;
  int32_t arr0[] = {1,2,3,4,5,6};
  run_test(arr0, SIZE_ARR(arr0), target);

  int32_t arr1[] = {1,2,3,4,5,6,11};
  run_test(arr1, SIZE_ARR(arr1), target);

  target = 51;
  int32_t arr2[] = {1, 4, 45, 6, 0, 19}; 
  run_test(arr2, SIZE_ARR(arr2), target);

  target = 9;
  int32_t arr3[] = {1, 10, 5, 2, 7}; 
  run_test(arr3, SIZE_ARR(arr3), target);

  target = 0;
  int32_t arr4[] = {-100, -90, -80, -60, 1}; 
  run_test(arr4, SIZE_ARR(arr4), target);

  target = 1;
  int32_t arr5[] = {1}; 
  run_test(arr5, SIZE_ARR(arr5), target);

  target = 1;
  int32_t arr6[] = {0}; 
  run_test(arr6, SIZE_ARR(arr6), target);

  target = 1;
  int32_t arr7[] = {}; 
  run_test(arr7, SIZE_ARR(arr7), target);

  return 0;
}