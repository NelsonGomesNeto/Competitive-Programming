#include <bits/stdc++.h>

int main()
{
  int n, amin, amax;
  while (scanf("%d %d %d", &n, &amin, &amax) != EOF)
  {
    int canGo = 0, height;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &height);
      canGo += height >= amin && height <= amax;
    }
    printf("%d\n", canGo);
  }
  return(0);
}