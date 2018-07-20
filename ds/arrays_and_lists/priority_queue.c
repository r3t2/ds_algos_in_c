#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<assert.h>

#define INITIAL_CAPACITY 32

/**
* P->L,R
* 0->1,2
* 1->3,4
* 2->5,6
*/
#define PARENT(x) (x-1)/2
#define LCHILD(x) 2*x + 1
#define RCHILD(x) 2*x + 2

int32_t max_cmp_int(void* x, void* y)
{
  return (*(int32_t*)x - *(int32_t*)y);
}

int32_t min_cmp_int(int32_t* x, int32_t* y)
{
  return (*x - *y) * -1;
}

static void swap(void* arr[], int32_t i, int32_t j)
{
  void* t = arr[i];
  arr[i] = arr[j];
  arr[j] = t;
}

typedef struct
{
  /** array to hold elements */
  void** arr;

  /** */
  uint32_t capacity;

  /** */
  uint32_t size;

  /** */
  int32_t (*comparator)(void*, void*);

} pq_handle_t;

pq_handle_t* pq_new(int32_t (*cmp)(void*, void*))
{
  pq_handle_t* h = calloc(1, sizeof(*h));
  if(h == NULL) return NULL;
  
  h->arr = calloc(INITIAL_CAPACITY, sizeof(*h->arr));
  h->capacity = INITIAL_CAPACITY;
  h->size = 0;
  h->comparator = cmp;

  return h;
}

static void pq_resize(pq_handle_t* h)
{

}

static void pq_swim(pq_handle_t* h, uint32_t i)
{
  int32_t cmp_res = (*h->comparator)(h->arr[i], h->arr[PARENT(i)]);
  while((cmp_res < 0) && (i != 0))
  {
    swap(h->arr, i, PARENT(i));
    i = PARENT(i);
    cmp_res = (*h->comparator)(h->arr[i], h->arr[PARENT(i)]);
  }

}

static void pq_sink(pq_handle_t* h, uint32_t i)
{

}

static void* pq_remove(pq_handle_t* h)
{
  /** assuming we don't store NULLs*/
  if(h->size==0) return NULL;
  void* ret = h->arr[0];

}
static void* pq_peek(pq_handle_t* h)
{

}
void pq_insert(pq_handle_t* h, void* data)
{
  if(h->size == h->capacity) pq_resize(h);
  assert(h->capacity > h->size);

  h->arr[h->size] = data;
  pq_swim(h, h->size);
}

static void run_test(int32_t N)
{
  pq_handle_t* h = pq_new(max_cmp_int);
  int32_t x, y;
  x=1;y=2;printf("cmp_res=%d, x=%d, y=%d\n", (*h->comparator)(&x,&y), x, y);
  x=1;y=1;printf("cmp_res=%d, x=%d, y=%d\n", (*h->comparator)(&x,&y), x, y);
}
int32_t main(void)
{
  run_test(10);
  return 0;
}