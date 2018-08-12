#include<stdio.h>
#include<stdint.h>

static void swap_chars(char * str, uint32_t i, uint32_t j)
{
  char t = str[i];
  str[i] = str[j];
  str[j] = t;
}
static uint32_t reverse_string_rec(char * str, uint32_t idx)
{
  if(str[idx] == '\0') return 0;

  uint32_t ret_idx = reverse_string_rec(str, idx+1);
  if(ret_idx < idx) swap_chars(str, ret_idx, idx);

  return ret_idx+1;

}
static void reverse_string_iter(char * str)
{
  /** If the string is NULL or empty, return.*/
  if(str == NULL) return;
  if(str[0] == '\0') return;

  /** st and end indexes the start and end of the string respectively*/
  uint32_t st = 0, end = 0;
  while(str[end+1] != '\0') end++;

  while(st<end)
  {
    swap_chars(str, st, end);
    st++; end--;
  }
}

static void run_test(char * str)
{
  printf("input         = %s\n", str);
  reverse_string_iter(str);
  printf("reversed iter = %s\n", str);
  reverse_string_rec(str, 0);
  printf("reversed rec  = %s\n", str);
  puts("");
}
int main(void)
{
  char str_0 []= "abcd"; run_test(str_0);
  char str_1 []= ""; run_test(str_1);
  char str_2 []= "a"; run_test(str_2);
  char str_3 []= "ab"; run_test(str_3);

  return 0;
}