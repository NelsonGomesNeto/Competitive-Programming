#include <stdio.h>
#include <math.h>

double treatZero(double ans)
{
  int lol = round(ans*100);
  return((double)lol/100);
}

int main()
{
  int t, i; scanf("%d", &t);
  for (i = 0; i < t; i ++)
  {
    if (i) printf("\n");

    int a, b, c; scanf("%dx^2 + %dx + %d", &a, &b, &c);
    int delta = b*b - 4 * a * c;

    printf("Test %d: %dx^2 + %dx + %d\n", i + 1, a, b, c);
    if (delta < 0)
      printf("SEM RESPOSTA\n");
    else if (delta == 0)
    {
      double x = ((double) -b / (2 * a));
      x = treatZero(x);
      printf("X = %.2lf\n", x);
    }
    else
    {
      double x1 = (double) (-b + sqrt(delta)) / (2 * a), x2 = (double) (-b - sqrt(delta)) / (2 * a);
      x1 = treatZero(x1); x2 = treatZero(x2);
      printf("X1 = %.2lf\nX2 = %.2lf\n", x1, x2);
    }
  }
  return(0);
}