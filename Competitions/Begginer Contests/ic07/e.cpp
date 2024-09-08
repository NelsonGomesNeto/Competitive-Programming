#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
  char s[4] = "abc";
  printf("%s\n", s);
  while (next_permutation(s, s + 3))
  {
    printf("%s\n", s);
  }
  return(0);
}
/*cba - abc
bca - acb
bac - bac
cab - bca
acb - cba
abc - cba


bca
cab
cba
*/
