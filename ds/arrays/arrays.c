#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** What region is this array in? rodata? What is rodata?*/
int32_t g_arr_0[10];

/** Where is this array located? */
int32_t g_arr_1[] = {1,2,3,4,5};

/** And this one? */
int32_t* g_ptr_0;

/** How about this one?*/
int32_t* g_ptr_1 = {5,4,3,2,1};

static void exp_1d_initialization(void)
{
  /** 
  Different types of initializing 1d arrays
  */

  /** Create an int32 array of size 10 on stack */
  int32_t m_arr_0[10];

  int32_t m_arr_1[] = {1,2,3,4,5};

  int32_t* m_ptr_0 = {5,4,3,2,1};

  int32_t* m_ptr_1 = malloc(5 * sizeof(*m_ptr_1));

  int32_t* m_ptr_2 = m_arr_0;

  uint32_t len_arr_0 = sizeof(m_arr_0)/sizeof(m_arr_0[0]);

  uint32_t len_arr_1 = sizeof(m_arr_1)/sizeof(m_arr_1[0]);

  uint32_t len_ptr_0 = sizeof(m_ptr_0)/sizeof(*m_ptr_0);

  uint32_t len_ptr_1 = sizeof(m_ptr_1)/sizeof(*m_ptr_1);

  uint32_t len_ptr_2 = sizeof(m_ptr_2)/sizeof(*m_ptr_2);

  printf("sizeof value returned by sizeof = %lu\n", sizeof(sizeof(char)));
  printf("sizeof size_t = %lu, sizeof int* = %lu, sizeof char* = %lu\n", sizeof(size_t), sizeof(int*), sizeof(char*));
  printf("sizeof int = %lu, int32 = %lu\n", sizeof(int), sizeof(int32_t));
  printf("int32_t m_arr_0[10]; sizeof(m_arr_0) = %lu, len_arr_0 = %lu\n", sizeof m_arr_0, len_arr_0);
  printf("len_arr_1 = %u\n", len_arr_1);
  printf("len_ptr_0 = %u\n", len_ptr_0);
  printf("len_ptr_1 = %u\n", len_ptr_1);
  printf("len_ptr_2 = %u\n", len_ptr_2);

}
int main(void)
{
  exp_1d_initialization();
  return 0;
}
