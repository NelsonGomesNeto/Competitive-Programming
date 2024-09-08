#include <stdio.h>

int main()
{
  int N, latas, copos, broke = 0;
  scanf("%i", &N);
  while (N > 0)
  {
    scanf("%i %i", &latas, &copos);
    if (latas > copos)
    {
      broke += copos;
    }
    N --;
  }
  printf("%i\n", broke);
  return(0);
}
