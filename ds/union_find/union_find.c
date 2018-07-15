#include <stdio.h>
#include <stdint.h> // explicitly sized datatypes
#include <stdlib.h> // malloc, calloc
#include <assert.h> // assert
#include <stdbool.h> // boolean typedef

/**
* Reference: https://algs4.cs.princeton.edu/15uf/
* Summary: Efficiently connect (union) N objects and find if two objects are connected.
* * Different types:
* * * Quick Union: O(tree height) union, O(tree height) find
* * * Quick Find: O(N) union, O(1) find.
* * * Weighted Quick Union: O(lg N) union, O(lg N) find.
* * * Weighted Quick Union w/ Path Compression: close to O(1). 
* Implementation: 
* * Implement Weighted Quick Union with path-halving.
* * Representation: Two arrays: id[] and size[].
* * 
* API:
* * uf_handle_t*  uf_new      (uint32_t N) : creates a handle for a union-find data structure for N objects
* * void          uf_union    (uf_handle_t* h, uint32_t p, uint32_t q): union of element p with q.
* * uint32_t      uf_find     (uf_handle_t* h, uint32_t p): component identifier for element p.
* * boolean       uf_connected(uf_handle_t* h, uint32_t p, uint32_t q): check if element p and q are connected
* * uint32_t      uf_count    (uf_handle_t* h): number of components
* * 
* * 
*/

#define PRINT_ARR(a, n) \
        for(uint32_t i=0; i<(n); i++) {printf("%u, ", a[i]);} 
typedef struct
{
  /** id array */
  uint32_t* id;
  /** size array */
  uint32_t* size;
  /** number of elements i.e., the number of objects on which union-find is being performed.*/
  uint32_t num_elements;
  /** number of components. Use uf_count() function instead.*/
  uint32_t num_components;

} uf_handle_t;

uf_handle_t* uf_new(uint32_t N)
{
  uf_handle_t* h = calloc(1, sizeof(*h));
  if(h==NULL) return NULL;
  printf("sizeof(*h)=%lu, sizeof(uf_handle_t)=%lu\n", sizeof(*h), sizeof(uf_handle_t));

  h->num_elements = N;
  h->num_components = N;

  /** use malloc since initializing every element below */
  h->id = malloc(N * sizeof(*(h->id)));
  h->size = malloc(N * sizeof(*(h->size)));
  printf("sizeof(*(h->id))=%lu, sizeof(uf_handle_t)=%lu\n", sizeof(*h), sizeof(uint32_t));
  printf("sizeof(*(h->size))=%lu, sizeof(uf_handle_t)=%lu\n", sizeof(*(h->size)), sizeof(uint32_t));

  uint32_t* id = h->id;
  uint32_t* sz = h->size;
  for(uint32_t i=0; i<N; i++)
  {
    id[i] = i; // link each component to itself.
    sz[i] = 1; // size of each component is 1.
  }

  return h;
}

// root function only visible in this implementation file
static uint32_t uf_root(uf_handle_t* h, uint32_t p)
{
  assert(h != NULL);
  assert(p < h->num_elements);

  uint32_t* id = h->id;
  // while(p != id[p]) p = id[p]; // p = parent of p. no path-halving.
  // implementing path-halving since it is single pass and simple
  while(p != id[p])
  {
    id[p] = id[id[p]]; // update the parent of p to grandparent of p. path-halving!!
    p = id[p];
  }

  return p;
}

void uf_union(uf_handle_t* h, uint32_t p, uint32_t q)
{
  /** error checking handled in root() */
  uint32_t rp = uf_root(h, p); // root of p's component
  uint32_t rq = uf_root(h, q); // root of q's component

  if(rp==rq) return; //p and q belong to same component. no need to union.

  uint32_t* id = h->id;
  uint32_t* sz = h->size;


  uint32_t sp = sz[rp]; // size of p's component
  uint32_t sq = sz[rq]; // size of q's component

  if(sp > sq) // p's component is larger
  {
    id[rq] = rp; // point root of q's component to p's root
    sz[rp] = sp + sq; // p's component size is sum of the two components
  }
  else
  {
    id[rp] = rq; // point root of p's component to q's root;
    sz[rq] = sp + sq; // q's component size is sum of the two components
  }

  h->num_components -= 1; // decrease the number of components by 1.

  return;
}

uint32_t uf_find(uf_handle_t* h, uint32_t p)
{
  return uf_root(h, p); // return the index of the root.
}

bool uf_connected(uf_handle_t* h, uint32_t p, uint32_t q)
{
  return uf_root(h, p) == uf_root(h, q); // if roots of p and q are same, they belong to same component
}

uint32_t uf_count(uf_handle_t* h)
{
  return h->num_components;
}
static void uf_print(uf_handle_t* h)
{
  if(h == NULL) return;
  printf("num_components = %u\n", h->num_components);
  printf("id = ["); PRINT_ARR(h->id, h->num_elements); printf("]\n");
  printf("sz = ["); PRINT_ARR(h->size, h->num_elements); printf("]\n");
}
static void run_test(uint32_t N)
{
  uf_handle_t* p_uf_h0 = uf_new(N);
  uint32_t* arr = malloc(N * sizeof(*arr));

  for(uint32_t i=0; i<N; i++) arr[i] = i;

  for(uint32_t i=0; i<10; i++)
  {
    uint32_t rp_idx = rand() % N;
    uint32_t rq_idx = rand() % N;
    printf("rp_idx=%u, rq_idx=%u\n", rp_idx, rq_idx);
    uf_union(p_uf_h0, rp_idx, rq_idx);
    uf_print(p_uf_h0);
    printf("------------\n");
  }


}
int32_t main(void)
{
  run_test(5);
  return 0;
}