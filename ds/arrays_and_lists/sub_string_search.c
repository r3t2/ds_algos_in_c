#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ERROR -2
#define NOT_FOUND -1


// static int32_t substring_rec2(char* s1, char* s2)
// {
//   printf("s1 =%s, s2 = %s\n", s1, s2);
//   /**
//   * If search string is empty, return 0;
//   */
//   if(s2[0]=='\0') return 0;
//   /**
//   * If s1 is empty but s2 is not empty, then s2 is not found in s1.
//   */
//   if(s1[0]=='\0') return NOT_FOUND;
  
//   uint32_t ret_idx = NOT_FOUND;
//   if(s1[0] == s2[0]) ret_idx = substring_rec2(s1+1, s2+1);
//   else if(s2[0]=='*') ret_idx = substring_rec2(s1+1, s2);
//   else ret_idx = NOT_FOUND;

//   printf("ret_idx = %d, s1=%s, s2=%s\n", ret_idx, s1, s2);

//   return ret_idx;
// }
static int32_t substring_rec(char* s1, char* s2)
{
  printf("s1=%s, s2=%s\n", s1, s2);
  /** s1 and s2 will NOT be NULL since this function will be called from within itself or substring()*/
  uint32_t idx1=0, idx2=0;

  if(s1[0] == '\0') return NOT_FOUND;
  if(s2[0] == '\0') return 0;



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
      if(ret_idx >= 0) return 0;
      idx1++;
    }
    else
    {
      return NOT_FOUND;
    }
  }

  if(s1[idx1] == '\0') return NOT_FOUND;
  else return 0;
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
    printf("idx=%d\n", idx);
    ret_idx = substring_rec(s1+idx, s2);
    printf("ret_idx=%d\n\n", ret_idx);

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

  // run_test("abcdefgh", "bcd");

  // run_test("abcdefgh", "fgh");

  // run_test("abcdefgh", "a*c");

  // run_test("abcdefgh", "a*b");

  // run_test("abcdefgh", "b*g");

  run_test("abcdefgh", "b*d*g");

  run_test("abcdefgh", "b*d*g*z");

  // run_test("abcdefgh", "b*z");

}