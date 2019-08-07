#include <stdio.h>

int main()
{
  int n, m;
  scanf("%d\n%d", &n, &m);
  while (n <= m)
  {
    if (n % 2 != 0)
    {
      printf("%d\n", n);
    }
    n ++;
  }
  return(0);
}
