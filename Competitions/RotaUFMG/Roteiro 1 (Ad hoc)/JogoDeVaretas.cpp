#include <bits/stdc++.h>

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int c, v, alone = 0, ret = 0;
    while (n -- > 0)
    {
      scanf("%d %d", &c, &v);
      ret += v / 4;
      alone += v % 4 > 1 ? 2 : 0;
    }
    ret += alone / 4;
    printf("%d\n", ret);
  }
  return(0);
}