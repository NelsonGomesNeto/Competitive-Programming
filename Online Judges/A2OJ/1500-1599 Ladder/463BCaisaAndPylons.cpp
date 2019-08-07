#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int h[n]; for (int i = 0; i < n; i ++) scanf("%d", &h[i]);

  int at = 0, energy = 0, dollars = 0;
  for (int i = 0; i < n; i ++)
  {
    if (energy + (at - h[i]) < 0)
    {
      dollars += h[i] - (at + energy);
      at += h[i] - (at + energy);
    }
    energy += at - h[i];
    at = h[i];
    // printf("%d %d - %d - %d %d\n", i, dollars, energy, at, h[i]);
  }

  printf("%d\n", dollars);

  return(0);
}