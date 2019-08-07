#include <stdio.h>

int main()
{
  int estoque, normal, week, weekBack = 1, SE, SA, DO, first = 0;
  scanf("%i\n%i\n%i", &estoque, &normal, &week);
  while (weekBack <= week)
  {
    estoque -= normal * 4;
    scanf("%i %i %i", &SE, &SA, &DO);
    estoque -= (SE + SA + DO);
    if (estoque <= 0 && first == 0)
    {
      week = weekBack;
      first ++;
    }
    weekBack ++;
  }
  if (estoque <=0)
  {
    printf("%i %i\n", week, estoque);
  }
  else
  {
    printf("%i\n", estoque);
  }
}
