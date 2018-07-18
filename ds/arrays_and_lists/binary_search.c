#include<stdio.h>
#include<stdint.h> // use datatype with explicit bitwidth
#include<stdbool.h> // use boolean data type
#include<stdlib.h> // rand()

bool binary_search_rec(int32_t* arr, int32_t target, uint32_t* res_idx, int32_t start, int32_t end)
{
  if(end < start) return false;

  uint32_t mid = (start + end)/2;

  if(arr[mid] == target) {*res_idx = mid; return true;}
  else if(arr[mid] > target) return binary_search_rec(arr, target, res_idx, start, mid-1);
  else return binary_search_rec(arr, target, res_idx, mid+1, end);

}
bool binary_search(int32_t* arr, int32_t len, int32_t target, uint32_t* res_idx)
{
  return binary_search_rec(arr, target, res_idx, 0, len);
}

static void run_test(int32_t* arr, int32_t len)
{
  printf("len = %u, input_arr = [", len);
  for(uint32_t i=0; i<len; i++) printf("%u, ", arr[i]);
  puts("]");

  uint32_t ret_idx;
  puts("test searching inside array");
  for(uint32_t i=0; i<len/2; i++)
  {
    uint32_t idx = rand() % len;
    binary_search(arr, len, arr[idx], &ret_idx);
    printf("searched for %d at idx = %u, ret_idx = %u, %s\n", arr[idx], idx, ret_idx, (idx==ret_idx?"PASSED":"FAILED"));
  }

  puts("test searching outside array");
  bool ret;
  ret = binary_search(arr, len, arr[0]-10, &ret_idx);
  printf("searched for %d, ret = %u, %s\n", arr[0]-10, ret, (ret==false?"PASSED":"FAILED"));
  ret = binary_search(arr, len, arr[len-1]+10, &ret_idx);
  printf("searched for %d, ret = %u, %s\n", arr[len-1]+10, ret, (ret==false?"PASSED":"FAILED"));
}

static int32_t cmp(const void* e1, const void* e2)
{
  int32_t x = *((int32_t*)e1);
  int32_t y = *((int32_t*)e2);
  return (x-y);
}
static void run_test_rand(uint32_t len)
{
  int32_t* arr = calloc(len, sizeof(*arr));
  for(uint32_t i=0; i<len; i++)
  {
    arr[i] = rand() % (len*4);
  }

  qsort(arr, len, sizeof(int32_t), cmp);

  printf("len = %u, input_arr = [", len);
  for(uint32_t i=0; i<len; i++) printf("%u, ", arr[i]);
  puts("]");

  uint32_t ret_idx;
  bool ret_val;
  for(uint32_t i=0; i<len/2; i++)
  {
    uint32_t rand_val = rand() % (len*2);
    ret_val = binary_search(arr, len, rand_val, &ret_idx);
    printf("searched for %d, ret_val = %u, ret_idx = %u\n", rand_val, ret_val, ret_idx);
  }
}

int32_t main(void)
{
  int32_t arr[] = {1,2,3,4,5,6,7,8,9,10};
  run_test(arr, sizeof(arr)/sizeof(arr[0]));

  puts("");
  run_test_rand(10);
  return 0;
}