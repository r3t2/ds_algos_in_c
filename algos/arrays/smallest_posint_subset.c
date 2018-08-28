/**
Find the smallest positive integer value that cannot be represented as sum of any subset of a given array
Given a sorted array (sorted in non-decreasing order) of positive numbers, find the smallest positive integer value that cannot be represented as sum of elements of any subset of given set. 
Expected time complexity is O(n).

Examples:

Input:  arr[] = {1, 3, 6, 10, 11, 15};
Output: 2

Input:  arr[] = {1, 1, 1, 1};
Output: 5

Input:  arr[] = {1, 1, 3, 4};
Output: 10

Input:  arr[] = {1, 2, 5, 10, 20, 40};
Output: 4

Input:  arr[] = {1, 2, 3, 4, 5, 6};
Output: 22
*/
#include <stdio.h>

#define PRINT_S32_ARR(arr, len) \
        printf("[ "); \
        for(int32_t i=0; i<(len); i++) \
          printf("%d, ", arr[i]);\
        printf("]\n");


/**
* input -- sorted array
* output -- smallest positive integer that cannot be a sum of any subset in arr
*/
int32_t smallest_pos_int(int32_t arr[], int32_t len)
{
  /** res is the value that cannot be represented by elements in array*/
  int32_t res = 1;

  for(int32_t i=0; i<len; i++)
  {
    /** If res is less than the next element, res is the first positive number that can't be represented by subset*/
    if(res < arr[i]) return res;

    /** 
    * 0 -- res-1 can be represented already. 
    * So the next number that cannot be represented is res + arr[i] after considering res[i].
    */
    res += arr[i];
  }

  return res;
}
static void run_test(int32_t arr[], int32_t len)
{
  printf("input = ");
  PRINT_S32_ARR(arr, len);

  printf("smallest pos int can't rep = %d\n", smallest_pos_int(arr, len));
}
int main(void)
{
  int32_t arr0[] = {1,2,3,4}; 
  run_test(arr0, sizeof(arr0)/sizeof(arr0[0]));

  int32_t arr1[] = {2,3,4}; 
  run_test(arr1, sizeof(arr1)/sizeof(arr1[0]));  

  int32_t arr2[] = {1,1,3,4}; 
  run_test(arr2, sizeof(arr2)/sizeof(arr2[0]));  

  int32_t arr3[] = {1,1,1,1}; 
  run_test(arr3, sizeof(arr3)/sizeof(arr3[0]));  

  int32_t arr4[] = {}; 
  run_test(arr4, sizeof(arr4)/sizeof(arr4[0]));  

  int32_t arr5[] = {1,2,3,4,5,6}; 
  run_test(arr5, sizeof(arr5)/sizeof(arr5[0]));

  return 0;
}