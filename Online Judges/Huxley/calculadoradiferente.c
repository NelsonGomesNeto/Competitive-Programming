#include <stdio.h>
#include <math.h>

int main()
{
  int A, B, n; float resultado; char oper;
  scanf("%d", &n);
  while (n > 0)
  {
    scanf("%d%c%d", &A, &oper, &B);
    if (oper == '#')
    {
      resultado = pow(A,B) * pow(B,A);
    }
    else if (oper == '@')
    {
      resultado = pow(A,B) / pow(B,A);
    }
    else if (oper == '&')
    {
      resultado = (B * sqrt(A)) + (A * sqrt(B));
    }
    else
    {
      resultado = (B * sqrt(A)) - (A * sqrt(B));
    }
    printf("%.2f\n", resultado);
    n --;
  }
  return(0);
}
