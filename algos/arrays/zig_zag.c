#include<stdio.h>
#include<stdint.h>

#define PRINT_INT32_ARR(str, x, N) \
        printf("%s = [", str);\
        for(uint32_t i=0; i<N; i++){ \
          printf("%d, ", x[i]); \
        } \
        printf("]\n");

#define RUN_TEST(arr) \
        run_test(arr, sizeof(arr)/sizeof(*arr));

void swap(int32_t* arr, int i, int j)
{
  int32_t t = arr[i];
  arr[i] = arr[j];
  arr[j] = t;
}
void zig_zag(int32_t* arr, uint32_t N)
{
  if(arr==NULL) return;
  if(N<=1) return;

  uint32_t i=1;
  uint32_t pp = 0;
  while(i<N)
  {
    if( ((pp==0) && (arr[i-1] > arr[i])) ||
        ((pp==1) && (arr[i-1] < arr[i])) )
    {
      swap(arr, i-1, i);
    }

    pp ^= 1;
    i++;
  }
}
static void run_test(int32_t* arr, uint32_t N)
{
  PRINT_INT32_ARR("input ", arr, N);
  zig_zag(arr, N);
  PRINT_INT32_ARR("output", arr, N);
  puts("");
}
int main(void)
{
  int32_t arr0[10] = {1, 2, 3, 4, 5, 6};
  RUN_TEST(arr0);

  int32_t arr1[] = {4, 3, 7, 8, 6, 2, 1};
  RUN_TEST(arr1);

  int32_t arr2[] = {};
  RUN_TEST(arr2);

  int32_t arr3[] = {1};
  RUN_TEST(arr3);

  int32_t arr4[] = {1, 2};
  RUN_TEST(arr4);

  int32_t arr5[] = {1, 2, 3};
  RUN_TEST(arr5);
  return 0;
}