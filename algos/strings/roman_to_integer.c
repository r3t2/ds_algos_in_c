/**
13. Roman to Integer
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: C = 100, L = 50, XXX = 30 and III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

static void check_valid(char c0, char c1)
{
  if((c0=='I') && !((c1=='V')||(c1=='X'))) assert(0);
  if((c0=='X') && !((c1=='L')||(c1=='C'))) assert(0);
  if((c0=='C') && !((c1=='D')||(c1=='M'))) assert(0);

}
uint32_t ro_value(char c)
{
  switch(c)
  {
    case '\0': return 0;
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: assert(0);
  }
}
uint32_t roman_to_int(const char* str)
{
  /** NULL and empty string return 0*/
  if(str==NULL) return 0;
  if(str[0]=='\0') return 0;

  uint32_t sum=0;
  uint32_t i=0;
  while(str[i] != '\0')
  {
    if(ro_value(str[i]) < ro_value(str[i+1]))
    {
      // good to check if it is a valid combination (falls within the 6 cases)
      check_valid(str[i], str[i+1]);
      sum += (ro_value(str[i+1]) - ro_value(str[i]));
      i += 2;
    }
    else
    {
      sum += ro_value(str[i]);
      i += 1;
    }
  }

  return sum;
}
static void run_test(const char * str)
{
  uint32_t int_value = roman_to_int(str);
  printf("roman_string=%s, int_value=%u\n\n", str, int_value);
}
int main(void)
{
  run_test("I");
  run_test("II");
  run_test("III");
  run_test("IV");
  run_test("IX");
  run_test("IXX");
  run_test("LVIII");
  run_test("MCMXCIV");
  return 0;
}