#include <stdio.h>

int main()
{
  int A, B, C;
  scanf("%i\n%i\n%i", &A, &B, &C);
  if (A == B && C != A)
  {
    printf("C\n");
  }
  else if (A == C && B != C)
  {
    printf("B\n");
  }
  else if (B == C && A != C)
  {
    printf("A\n");
  }
  else
  {
    printf("*\n");
  }
  return(0);
}
