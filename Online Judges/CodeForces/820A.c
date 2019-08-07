#include <stdio.h>

int main()
{
  int pages, initial, max, accelaration, previous;
  scanf("%d %d %d %d %d", &pages, &initial, &max, &accelaration, &previous);

  int days = 1;
  pages -= initial;
  initial += accelaration;
  if (initial > max)
    initial = max;
  while (pages > 0)
  {
    pages += previous;
    pages -= initial;
    initial += accelaration;
    if (initial > max)
      initial = max;
    days ++;
  }
  printf("%d\n", days);
  return(0);
}
