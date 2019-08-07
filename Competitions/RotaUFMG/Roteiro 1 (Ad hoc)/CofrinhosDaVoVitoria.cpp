#include <bits/stdc++.h>

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    printf("\nTeste %d\n", ++ t);

    int tj = 0, tz = 0;
    while (n -- > 0)
    {
      int j, z; scanf("%d %d", &j, &z);
      tj += j; tz += z;
      printf("%d\n", tj - tz);
    }
  }
  return(0);
}