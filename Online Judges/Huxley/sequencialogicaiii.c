#include <stdio.h>

int main()
{
  int barraN, target, jump, x = 1, pula = 1;
  scanf("%d %d %d", &barraN, &target, &jump);
  for (x = 1; x <= target; x += jump, pula ++)
  {
    if (pula == barraN)
    {
      printf("%d\n", x); pula = 0;
    }
    else
    {
      printf("%d ", x);
    }
  }
  printf("\n");
  return(0);
}
