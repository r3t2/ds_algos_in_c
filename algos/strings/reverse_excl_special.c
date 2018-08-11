#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/**
Reverse an array without affecting special characters
Given a string, that contains special character together with alphabets (‘a’ to ‘z’ and ‘A’ to ‘Z’), reverse the string in a way that special characters are not affected.

Examples:

Input:   str = "a,b$c"
Output:  str = "c,b$a"
Note that $ and , are not moved anywhere.  
Only subsequence "abc" is reversed

Input:   str = "Ab,c,de!$"
Output:  str = "ed,c,bA!$"
*/

#define MAX_IN_STRING_SIZE 100

static void swap_chars(char * str, uint32_t i, uint32_t j)
{
  char t = str[i];
  str[i] = str[j];
  str[j] = t;
}

static bool is_special(char c)
{
  bool ret_val = !( (c>='0' && c<='9') || 
                    (c>='A' && c<='Z') || 
                    (c>='a' && c<='z')  );
  return ret_val;
}
/**
* In-place two-pass algorithm.
* O(1) and O(N) space and time complexity.
*/
void reverse_string_excl_special(char * str)
{
  if(str == NULL) return; // null string --> no work or ERROR/ASSERT
  if(str[0] == '\0') return; // empty string --> no work

  uint32_t st = 0, end = 0;
  while(str[end+1] != '\0') end++; //variable end indexes the last char

  while(st < end)
  {
    while((st<end) && (str[st]!='\0') && is_special(str[st]))   st++;
    while((st<end) && (end>0)         && is_special(str[end]))  end--;
    swap_chars(str, st, end);
    st++; end--;
  }
  return ;
}

static void run_test(char * str)
{
  printf("input  = %s\n", str);
  reverse_string_excl_special(str);
  printf("output = %s\n\n", str);
}
int main(void)
{
  char * arg_str = malloc(MAX_IN_STRING_SIZE * sizeof(*arg_str));
  char * str_lit = NULL;

  str_lit=""; strcpy(arg_str, str_lit); run_test(arg_str);
  str_lit="abc"; strcpy(arg_str, str_lit); run_test(arg_str);
  str_lit="ab"; strcpy(arg_str, str_lit); run_test(arg_str);
  str_lit="a"; strcpy(arg_str, str_lit); run_test(arg_str);
  str_lit="a&b&c"; strcpy(arg_str, str_lit); run_test(arg_str);
  str_lit="a&b&."; strcpy(arg_str, str_lit); run_test(arg_str);

  return 0;
}