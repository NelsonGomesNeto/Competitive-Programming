#include <stdio.h>

int main()
{
  int N, P, Q;
  char oper;
  scanf("%i", &N);
  scanf("%i %c %i", &P, &oper, &Q);
  if (oper == '+')
  {
    if (N >= P + Q)
    {
      printf("OK\n");
    }
    else
    {
      printf("OVERFLOW\n");
    }
  }
  else
  {
    if (N >= P * Q)
    {
      printf("OK\n");
    }
    else
    {
      printf("OVERFLOW\n");
    }
  }
  return(0);
}
