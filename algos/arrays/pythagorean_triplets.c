#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 32


#define PRINT_S32_ARR(arr, len) \
        printf("[ "); \
        for(int32_t i=0; i<(len); i++) \
          printf("%d, ", arr[i]);\
        printf("]\n");

/** Fake hash set of integers. 
* hash_set only in API. 
* Didn't really implement O(1) expected run time lookup
*/
typedef struct hash_set_handle
{
  int32_t *arr;
  int32_t capacity;
  
  int32_t size;

  /** Not used since didn't implement a hash set*/
  int32_t (*hash_func)(void *);

} hash_set_handle;

hash_set_handle* hash_set_new()
{
  hash_set_handle* h = malloc(1 * sizeof(hash_set_handle));
  h->size = 0;

  h->arr = calloc(INITIAL_CAPACITY, sizeof(int32_t));
  h->capacity = INITIAL_CAPACITY;

  return h;
}

void hash_set_add(hash_set_handle* h, int32_t e)
{
  //if(h->size==h->capacity) hash_set_resize(h);
  h->arr[h->size] = e;
  h->size++;
}

bool hash_set_find(hash_set_handle* h, int32_t key)
{
  for(int32_t i=0; i<h->size; i++)
  {
    if(key == h->arr[i]) return true;
  }

  return false;
}

bool has_pythagorean_triplet(int32_t arr[], int32_t len)
{
  int32_t arr_sq[len];
  hash_set_handle* h = hash_set_new();

  for(int32_t i=0; i<len; i++)
  {
    arr_sq[i] = arr[i]*arr[i];
    hash_set_add(h, arr_sq[i]);
  }

  for(int32_t i=0; i<len-1; i++)
  {
    for(int32_t j=i+1; j<len; j++)
    {
      int32_t sum = arr_sq[i] + arr_sq[j];
      if(hash_set_find(h, sum))
      {
        printf("triplet found. i=%d, j=%d\n", i, j);
        return true;
      }
    }
  }
  return false;
}

static void run_test(int32_t arr[], int32_t len)
{
  printf("input = ");
  PRINT_S32_ARR(arr, len);

  printf("has pythagorean triplet = %u\n", has_pythagorean_triplet(arr, len));
}
int main(void)
{
  int32_t arr0[] = {1,2,3,4,5,6};
  run_test(arr0, sizeof(arr0)/sizeof(arr0[0]));


  return 0;
}