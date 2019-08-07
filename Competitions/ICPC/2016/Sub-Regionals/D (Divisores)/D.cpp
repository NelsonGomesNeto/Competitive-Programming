#include <stdio.h>
#include <math.h>

int main()
{
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);

  int i, k;
  for (i = 1; i <= sqrt(c); i ++)
  {
    k = a * i;
    if (k % b != 0 && c % k == 0 && d % k != 0)
    {
      printf("%d\n", k);
      return(0);
    }
  }
  printf("-1\n");
  return(0);
}
