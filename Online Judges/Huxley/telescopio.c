#include <stdio.h>

int main()
{
  int abertura, tests, fotons, star = 0;
  scanf("%i\n%i", &abertura, &tests);
  while (tests > 0)
  {
    scanf("%i", &fotons);
    if (abertura * fotons >= 40000000)
    {
      star ++;
    }
    tests --;
  }
  printf("%i\n", star);
  return(0);
}
