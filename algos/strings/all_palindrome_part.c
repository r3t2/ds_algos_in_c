#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/**
* input:  c_arr     -- char array to be checked if it is a palindrome between st and end indices
*         st        -- starting index to check for palindrome
*         end       -- ending index to check for palindrome. c_arr[st+i] is compared with c_arr[end-i]
* output: bool      -- true if it is a palindrome
*                   -- false if it is not
* Does not check if c_arr is at least of size len. It compares c_arr[0] with c_arr[len-1]
*/
static bool is_palindrome(const char c_arr[], int32_t st, int32_t end)
{
  if(c_arr == NULL) return false;
  if(st > end) return false;

  while(st<=end)
  {
    if(c_arr[st] != c_arr[end]) return false;

    st++;
    end--;
  }
  return true;
}

void all_palin_parts_iter(char * str)
{
  uint32_t len = strlen(str);

  for(uint32_t st=0; st<len; st++)
  {
    for(uint32_t end=st; end<len; end++)
    {
      if(is_palindrome(str, st, end))
      {
        printf("%.*s,", end-st+1, str+st);
      }
    }
  }

}

static void run_test(char * str)
{
  all_palin_parts_iter(str);
  printf("\n");
}

static void run_test_palin(char * str)
{
  uint32_t len = strlen(str);
  printf("input = %s, strlen = %u, ", str, len);
  printf("is_palindrome = %u\n", is_palindrome(str, 0, len-1));
}

int main(void)
{
  run_test_palin("");
  run_test_palin("aba");
  run_test_palin("aa");
  run_test_palin("ab");
  run_test_palin("abc");
  run_test_palin("a");

  printf("\n");
  run_test("abc");
  run_test("aba");
  run_test("aaa");
  run_test("");
  run_test("aa");
  run_test("ab");
  run_test("a");

  return 0;
}