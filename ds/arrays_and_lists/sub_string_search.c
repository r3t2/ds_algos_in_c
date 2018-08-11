#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ERROR -2
#define NOT_FOUND -1
/**
* The following two functions can be combined but due to time constraints, 
* I am not able to work on the refactoring.
*/
static int32_t substring_rec(char* s1, char* s2)
{
  /** 
  * s1 and s2 will NOT be NULL since this function will be called from within itself or substring()
  */
  uint32_t idx1=0, idx2=0;

  while( (s1[idx1]!='\0') && (s2[idx2]!='\0') )
  {
    if(s1[idx1] == s2[idx2])
    {
      idx1++;
      idx2++;
    }
    else if(s2[idx2] == '*')
    {
      int32_t ret_idx = substring_rec(s1+idx1, s2+idx2+1);
      if(ret_idx >= 0) return idx1;
      idx1++;
    }
    else
    {
      return NOT_FOUND;
    }
  }

  if(s2[idx2] == '\0') return 0;
  else return NOT_FOUND;
  
}

/**
* Finding s2 in s1.
* s1 is the larger string
* s2 is smaller string
*/
int32_t substring(char* s1, char* s2)
{
  /**
  * If either of the strings are NULL, return ERROR
  */
  if(s1==NULL || s2==NULL) return ERROR;

  uint32_t idx = 0;
  int32_t ret_idx = NOT_FOUND;

  while(s1[idx]!='\0' && ret_idx<0)
  {
    ret_idx = substring_rec(s1+idx, s2);
    if(ret_idx >= 0) return idx;
    idx++;
  }

  return NOT_FOUND;
}


static void run_test(char* s1, char*s2)
{
  printf("s1 = %s, s2 = %s\n", s1, s2);
  int32_t ret_idx = substring(s1, s2);
  printf("ret_idx = %d\n\n", ret_idx);
}

int main(void)
{
  run_test("abc", "bc");

  run_test("a", "b");

  run_test("a", "");

  run_test("", "a");

  run_test("abcdefgh", "bcd");

  run_test("abcdefgh", "fgh");

  run_test("abcdefgh", "a*c");

  run_test("abcdefgh", "a*b");

  run_test("abcdefgh", "b*g");

  run_test("abcdefgh", "b*d*g");

  run_test("abcdefgh", "b*d*g*z");

  run_test("abcdefgh", "b*z");

  run_test("abcdefgeeez", "e*z");

  run_test("abcdefgeeez", "e*zh");

}
/** 
############
Output from console
############

s1 = abc, s2 = bc
ret_idx = 1

s1 = a, s2 = b
ret_idx = -1

s1 = a, s2 = 
ret_idx = 0

s1 = , s2 = a
ret_idx = -1

s1 = abcdefgh, s2 = bcd
ret_idx = 1

s1 = abcdefgh, s2 = fgh
ret_idx = 5

s1 = abcdefgh, s2 = a*c
ret_idx = 0

s1 = abcdefgh, s2 = a*b
ret_idx = 0

s1 = abcdefgh, s2 = b*g
ret_idx = 1

s1 = abcdefgh, s2 = b*d*g
ret_idx = 1

s1 = abcdefgh, s2 = b*d*g*z
ret_idx = -1

s1 = abcdefgh, s2 = b*z
ret_idx = -1

s1 = abcdefgeeez, s2 = e*z
ret_idx = 4

s1 = abcdefgeeez, s2 = e*zh
ret_idx = -1
*/