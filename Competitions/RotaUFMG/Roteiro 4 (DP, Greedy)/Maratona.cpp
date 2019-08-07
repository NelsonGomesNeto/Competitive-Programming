#include <bits/stdc++.h>

int main()
{
  int n, m, d, prev = 0; scanf("%d %d", &n, &m);
  int can = 1;
  while (n --)
  {
    scanf("%d", &d);
    if (d - prev > m) can = 0;
    prev = d;
  }
  if (42195 - prev > m) can = 0;
  printf("%s\n", can ? "S" : "N");
  return(0);
}