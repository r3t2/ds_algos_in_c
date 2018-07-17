#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/** Implementation of dynamically resizeable array. Similar to ArrayList 
* API:
* darr_handle_t* darr_new() : create an empty array.
* void darr_append(darr_handle_t* h, void* data) : add to the end of the list
* void* darr_get(darr_handle_t* h, int idx) : get data at idx
* void darr_replace(darr_handle_t* h, int idx, void* data) : replace the element at idx with data.
* uint32_t darr_size(darr_handle_t* h) : number of the elements in this array
* void* darr_delete(darr_handle_t* h, uint32_t idx) : remove element from idx
*/

/** Pointer stuffing similar to glib */
#define PTR_TO_UINT32(x)  ((uint32_t) (x))
#define UINT32_TO_PTR(x)  ((void*)    (x))
#define PTR_TO_INT32(x)   ((int32_t)  (x))
#define INT32_TO_PTR(x)   ((void*)    (x))

#define INITIAL_CAPACITY 2
typedef struct 
{
  /** Array to contain store pointers to arbitrary data elements*/
  void** arr;

  /** current arr capacity */
  uint32_t curr_capacity;

  /** number of elements*/
  uint32_t size;
}darr_handle_t;

darr_handle_t* darr_new()
{
  darr_handle_t* h = malloc(1* sizeof(*h));
  h->curr_capacity = INITIAL_CAPACITY;
  h->size = 0;
  h->arr = calloc(INITIAL_CAPACITY, sizeof(*h->arr));
  printf("sizeof void*=%lu, sizeof *h->arr=%lu\n", sizeof(void*), sizeof(*h->arr));

  return h;
}


bool darr_resize(darr_handle_t* h)
{
  void** old_arr = h->arr;
  printf("resizing. begin capacity = %u, ", h->curr_capacity);
  if(h->size == h->curr_capacity)
  {
    h->arr = calloc(h->curr_capacity*2, sizeof(*h->arr));
    if(h->arr == NULL) return false;
    h->curr_capacity *= 2;
  }
  else
  {
    h->arr = calloc(h->curr_capacity/2, sizeof(*h->arr));
    if(h->arr == NULL) return false;
    h->curr_capacity /= 2;
  }

  for(uint32_t i=0; i<h->size; i++)
  {
    h->arr[i] = old_arr[i];
  }
  printf(" end capacity = %u\n", h->curr_capacity);
  return true;
}

void darr_append(darr_handle_t* h, void* data)
{
  if(h->size == h->curr_capacity) darr_resize(h);
  /** TODO: handle resizing failure better */
  assert(h->size < h->curr_capacity);

  h->arr[h->size] = data;
  h->size++;
}

void* darr_get(darr_handle_t* h, uint32_t idx)
{
  assert(idx < h->size);
  return h->arr[idx];
}

void darr_replace(darr_handle_t* h, uint32_t idx, void* data)
{
  assert(idx < h->size);
  h->arr[idx] = data;
}

uint32_t darr_size(darr_handle_t* h)
{
  return h->size;
}

void* darr_delete(darr_handle_t* h, uint32_t idx)
{
  assert(idx<h->size);
  void* tmp = h->arr[idx];
  for(uint32_t i=idx; i<(h->size-1); i++)
  {
    h->arr[i] = h->arr[i+1];
  }
  h->size--;
  if((h->curr_capacity > INITIAL_CAPACITY) && (h->size < h->curr_capacity/2)) darr_resize(h);

  return tmp;
}

void* darr_delete_last(darr_handle_t* h)
{
  assert(h->size > 0);
  void* tmp = h->arr[h->size-1];
  h->size--;
  return tmp;
}


static void run_test(int N)
{
  darr_handle_t* p_darr_h0 = darr_new();
  puts("inserting elements");
  for(uint32_t i=0; i<N; i++)
  {
    printf("%u, ", i);
    darr_append(p_darr_h0, UINT32_TO_PTR(i));
  }
  puts("");

  puts("removing elements");
  for(uint32_t i=0; i<N; i++)
  {
    printf("%u, ", PTR_TO_UINT32(darr_delete(p_darr_h0, 0)));
  }
  puts("");


}
int32_t main(void)
{
  run_test(10);
  run_test(100);

  return 0;
}