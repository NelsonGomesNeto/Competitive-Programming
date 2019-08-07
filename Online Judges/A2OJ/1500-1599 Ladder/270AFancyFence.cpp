#include <bits/stdc++.h>

int regularPolygon(int n)
{
  return((360 % (180 - n)) == 0);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    printf("%s\n", regularPolygon(n) ? "YES" : "NO");
  }
  return(0);
}