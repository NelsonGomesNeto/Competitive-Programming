#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int a[n], minimum = 1000000001, pos;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    if (a[i] < minimum)
    {
      minimum = a[i];
      pos = i;
    }
  }

  for (int i = 0; i < n; i ++)
    a[i] -= minimum;

  int at = minimum % n, forward = 0;
  while ((a[at] - forward) > 0)
  {
    at = (at + 1) % n;
    forward ++;
  }

  printf("%d\n", at + 1);

  return(0);
}