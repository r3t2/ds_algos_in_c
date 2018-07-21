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
#define PARENT(x) ((x-1)/2)
#define LCHILD(x) (2*x + 1)
#define RCHILD(x) (2*x + 2)
#define ROOT             0

#define INT_TO_PTR(x) ((void*) (x))
#define PTR_TO_INT(x) ((int32_t) (x))

int32_t max_cmp_int(void* x, void* y)
{
  return PTR_TO_INT(x) - PTR_TO_INT(y);
}

int32_t min_cmp_int(int32_t* x, int32_t* y)
{
  return (PTR_TO_INT(x) - PTR_TO_INT(y)) * -1;
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

static void pq_swim(pq_handle_t* h, int32_t i)
{
  if(h->size <= 1) return;

  void** arr = h->arr;
  int32_t (*p_cmp)(void*, void*) = h->comparator;
  
  /** 
  * compare child with parent order: (child, parent) === (i, PARENT(i))
  * if compare result < 0, swap child and parent. i.e., child moves up.
  */
  
  int32_t cmp_res = (*p_cmp)(arr[i], arr[PARENT(i)]);
  while((cmp_res < 0) && (i != ROOT))
  {
    swap(arr, i, PARENT(i));
    i = PARENT(i);
    if(i==ROOT) return;
    cmp_res = (*p_cmp)(arr[i], arr[PARENT(i)]);
  }

}

static inline int32_t pq_min_child_idx(pq_handle_t* h, int32_t i)
{
  if(LCHILD(i) >= h->size) return -1; // no child exists
  if(RCHILD(i) >= h->size) return LCHILD(i); // only left child exists.

  /** At least two children exist. Compare and return min*/
  int32_t cmp_res = (*h->comparator)(h->arr[LCHILD(i)], h->arr[RCHILD(i)]);
  if(cmp_res < 0) return LCHILD(i);
  else return RCHILD(i);
}

static void pq_sink(pq_handle_t* h, uint32_t i)
{
  if(h->size <= 1) return;

  void** arr = h->arr;
  int32_t (*p_cmp)(void*, void*) = h->comparator;
  
  /** 
  * compare child with parent order: (child, parent) === (i, PARENT(i))
  * if compare result < 0, swap child and parent. i.e., child moves up.
  */
  uint32_t min_child_idx = pq_min_child_idx(h, i);  // this will not return invalid idx since we checked if size==1 earlier
  int32_t cmp_res = (*p_cmp)(arr[i], arr[min_child_idx]);

  //printf("i=%d, min_child_idx=%d, cmp_res=%d\n", i, min_child_idx, cmp_res);
  
  /** while the element at i is "greater" its child*/
  while((cmp_res > 0))
  {
    swap(arr, i, min_child_idx);
    
    i = min_child_idx;
    min_child_idx = pq_min_child_idx(h, i);
    
    /** if child does not exist return*/
    if(min_child_idx == -1) return;
    
    cmp_res = (*p_cmp)(arr[i], arr[PARENT(i)]);
  }
}

void* pq_remove(pq_handle_t* h)
{
  /** assuming we don't store NULLs*/
  if(h->size==0) return NULL;
  
  void* ret = h->arr[ROOT];
  h->arr[ROOT] = h->arr[h->size-1];
  h->arr[h->size-1] = NULL; // do not save pointers of elements deleted from pq.
  h->size--;

  pq_sink(h, ROOT);

  if(h->size < h->capacity/2) pq_resize(h);

  return ret;
}
void* pq_peek(pq_handle_t* h)
{
  if(h->size == 0) return NULL;
  return h->arr[ROOT];
}
void pq_insert(pq_handle_t* h, void* data)
{
  if(h->size == h->capacity) pq_resize(h);
  assert(h->capacity > h->size);

  h->arr[h->size] = data;
  h->size++;
  pq_swim(h, h->size-1);

}

static void pq_print(pq_handle_t* h)
{
  printf("size = %d\nelements=[", h->size);
  for(int32_t i=0; i<h->size; i++)
  {
    printf("%d, ", PTR_TO_INT(h->arr[i]));
  }
  puts("]");
}
static void experiment()
{
  pq_handle_t* h = pq_new(max_cmp_int);
  int32_t x, y;
  int32_t (*ptr_cmp_func)(void*, void*) = h->comparator;
  x=1;y=2;printf("cmp_res=%d, x=%d, y=%d\n", (*ptr_cmp_func)(&x,&y), x, y);
  x=1;y=1;printf("cmp_res=%d, x=%d, y=%d\n", (*h->comparator)(&x,&y), x, y);
  x=2;y=1;printf("cmp_res=%d, x=%d, y=%d\n", (*h->comparator)(&x,&y), x, y);

  int32_t i;
  i=0; printf("i=%d, PARENT(i)=%d, LCHILD(i)=%d, RCHILD(i)=%d\n", i, PARENT(i), LCHILD(i), RCHILD(i));
  i=1; printf("i=%d, PARENT(i)=%d, LCHILD(i)=%d, RCHILD(i)=%d\n", i, PARENT(i), LCHILD(i), RCHILD(i));
  i=2; printf("i=%d, PARENT(i)=%d, LCHILD(i)=%d, RCHILD(i)=%d\n", i, PARENT(i), LCHILD(i), RCHILD(i));
  i=3; printf("i=%d, PARENT(i)=%d, LCHILD(i)=%d, RCHILD(i)=%d\n", i, PARENT(i), LCHILD(i), RCHILD(i));
}
static void run_test(int32_t N)
{
  pq_handle_t* h = pq_new(max_cmp_int);
  if(h == NULL) puts("Could not allocate new PQ handle");
  printf("N = %d\n", N);

  printf("inserting: ");
  for(int32_t i=0; i<N; i++)
  {
    int32_t n = rand() % N;
    printf("%d, ", n);
    pq_insert(h, INT_TO_PTR(n));
  }
  puts("");
  printf("size = %d, expected = %d\n", h->size, N);

  printf("\nprinting pq\n");
  pq_print(h);

  printf("\nremoving: ");
  for(int32_t i=0; i<N; i++)
  {
    int32_t n = PTR_TO_INT(pq_remove(h));
    printf("%d, ", n);
  }
  puts("");
  printf("size = %d, expected = %d\n", h->size, 0);

}
int32_t main(void)
{
  experiment();
  run_test(10);
  run_test(30);

  return 0;
}