#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

/**
Structure to define a linked list node.
*/
/** Forward definition needed to use the typedef-ed name in defining the structure itself*/
typedef struct sll_node_t sll_node_t;
struct sll_node_t
{
  void* data;
  sll_node_t* next;
};

/**
Structure to define a linked list handle.
*/
typedef struct
{
  /** Reference to the head of the list */
  sll_node_t* head;
  /** Reference to the tail of the list */
  sll_node_t* tail;
  /** Number of elements in this list */
  uint32_t size;
} sll_handle_t;

/** TODO: Explore the following: 
1. Using const
2. Using static
3. Using inline
4. Macros
*/
/** create a new node give data and pointer to next node */
sll_node_t* sll_new_node(void* data, sll_node_t* next)
{
  sll_node_t* new_node = malloc(1* sizeof(sll_node_t));
  if(new_node == NULL) return NULL;
  new_node->data = data;
  new_node->next = next;

  return new_node;
}

/** insert at head */
bool sll_insert_head(sll_handle_t* h, void* data)
{
  sll_node_t* new_node = sll_new_node(data, h->head);
  if(new_node == NULL) return false;
  
  if(h->tail == NULL) h->tail = new_node;

  // printf("inserted: data = %p, *data = %u\n", new_node->data, *(uint32_t*)new_node->data);
  h->head = new_node;
  h->size += 1;
  return true;
}

/** insert at tail */
void sll_insert_tail(sll_handle_t *h, void * data)
{
  sll_node_t* new_node = sll_new_node(data, NULL);
  if(h->size == 0) h->head = new_node;
  else h->tail->next = new_node;

  h->tail = new_node;
  h->size += 1;
}
void sll_print(sll_handle_t *h)
{
  printf("size = %u\n", h->size);
  sll_node_t* start = h->head;
  printf("data = [");
  while(start != NULL)
  {
    printf("(%p, %u), ", start->data, *((uint32_t*)start->data));
    start = start->next;
  }
  printf("]\n");
}
/** remove from head */
void* sll_remove_head(sll_handle_t *h)
{
  if(h->size == 0) return NULL;
  sll_node_t* node = h->head;

  void* data = node->data;
  h->head = node->next;

  free(node);
  h->size -= 1;

  return data;
}

static void run_test(int32_t* a, uint32_t len)
{
  printf("input length = %u\n", len);
  printf("input data   = [ ");
  for(uint32_t i=0; i<len; i++)
  {
    printf("%u ", a[i]);
  }
  printf("]\n\n");

  
  sll_handle_t* h1 = calloc(1, sizeof(*h1));
  sll_handle_t* h2 = calloc(1, sizeof(*h2));
  /*sll_handle_t h0;
  printf("sizeof sll_handle_t = %lx, h1 = %lx, h0 = %lx\n", sizeof(sll_handle_t), sizeof(h1), sizeof(h0));
  printf("sizeof node_t = %lx\n", sizeof(sll_node_t));
  printf("h1        = %p, h2        = %p\n", h1, h2);
  printf("h1->size  = %p, h2->size  = %p\n\n", &h1->size, &h2->size);*/

  for(uint32_t i=0; i<len; i++)
  {
    sll_insert_head(h1, &a[i]);
    sll_insert_tail(h2, &a[i]);
  }

  printf("list after inserting at head: \n"); sll_print(h1);
  printf("list after inserting at tail: \n"); sll_print(h2);
  printf("\n");

  int32_t d;
  printf("removing from list: ");
  for(uint32_t i=0; i<len; i++)
  {
    d = *(int32_t*)sll_remove_head(h1);
    printf("%d, ",d);
  }
  printf("\n");

}

int main(void)
{
  int32_t a[] = {1,2,3,4,5};
  run_test(a, sizeof(a)/sizeof(a[0]));
  return 0;
}