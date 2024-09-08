#include <stdio.h>

int main()
{
  int N, divi, total = 0;
  scanf("%i", &N);
  while (N > 0)
  {
    scanf("%i", &divi);
    total += (divi - 1);
    N --;
  }
  printf("%i\n", total);
  return(0);
}
