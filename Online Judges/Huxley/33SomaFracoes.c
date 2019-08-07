#include <stdio.h>
#define DEBUG if(0)

int main()
{
  int a, b, c, d, p, q;
  scanf("%d/%d + %d/%d", &a, &b, &c, &d);

  p = a * d + b * c;
  q = b * d;
  DEBUG printf("%d/%d\n", p, q);

  int smallest, i;
  if (p < q)
    smallest = p;
  else
    smallest = q;

  for (i = 2; i <= smallest; i ++)
    while (p % i == 0 && q % i == 0)
    {
      p /= i;
      q /= i;
    }

  if (b == 0 || d == 0)
    printf("entrada invalida!\n");
  else
    printf("%d/%d\n", p, q);

  return(0);
}