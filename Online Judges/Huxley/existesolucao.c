#include <stdio.h>

int main()
{
  int A, B, C, limitA, limitB, checkA, checkB; scanf("%d %d %d", &A, &B, &C);
  if (A == 0)
  {
    if (C % A > 0)
    {
      printf("N\n");
    }
    else
    {
      printf("S\n");
    }
  }
  else if (B == 0)
  {
    if (C % B > 0)
    {
      printf("N\n");
    }
    else
    {
      printf("S\n");
    }
  }
  else
  {
    limitA = (C / A) + 1;
    limitB = (C / B) + 1;
    for (checkA = 0; checkA < limitA; checkA ++)
    {
      for (checkB = 0; checkB < limitB; checkB ++)
      {
        if ((checkA * A) + (checkB * B) == C)
        {
          printf("S\n");
          return(0);
        }
      }
    }
    printf("N\n");
  }
  return(0);
}
