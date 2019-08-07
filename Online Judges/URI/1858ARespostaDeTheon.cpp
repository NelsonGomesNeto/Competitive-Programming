#include <bits/stdc++.h>

int main()
{
  int n, t, minT = 1<<20, pos; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &t);
    if (t < minT)
      minT = t, pos = i;
  }
  printf("%d\n", pos + 1);
  return(0);
}