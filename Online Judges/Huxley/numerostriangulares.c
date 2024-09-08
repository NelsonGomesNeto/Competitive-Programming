#include <stdio.h>

int main()
{
  int nesimo, repeat, soma = 0, total = 0; scanf("%d", &nesimo);
  for (repeat = 1; repeat <= nesimo; repeat ++)
  {
    soma += repeat;
    total += soma;
  }
  if (soma % 2 == 0 && total % 2 == 0)
  {
    printf("%d %d P\n", soma, total);
  }
  else if (soma % 2 != 0 && total % 2 != 0)
  {
    printf("%d %d I\n", soma, total);
  }
  else
  {
    printf("%d %d N\n", soma, total);
  }
  return(0);
}
