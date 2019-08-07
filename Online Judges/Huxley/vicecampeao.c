#include <stdio.h>

int main()
{
  int A, B, C;
  scanf("%i %i %i", &A, &B, &C);
  if (A >= B && A <= C || A >= C && A <= B)
  {
    printf("%i\n", A);
  }
  else if (B >= A && B <= C || B >= C && B <= A)
  {
    printf("%i\n", B);
  }
  else
  {
    printf("%i\n", C);
  }
  return(0);
}
