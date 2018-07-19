#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#define INITIAL_CAPACITY 32

int32_t max_cmp_int(int32_t* x, int32_t* y)
{
  return (*x - *y);
}

int32_t min_cmp_int(int32_t* x, int32_t* y)
{
  return (*y - *x);
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

void pq_insert(pq_handle_t* h, void* data)
{
  
}

static void run_test(int32_t N)
{

}
int32_t main(void)
{
  run_test(10);
  return 0;
}