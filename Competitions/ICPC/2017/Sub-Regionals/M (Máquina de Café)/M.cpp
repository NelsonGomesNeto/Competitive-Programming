#include <bits/stdc++.h>

int main()
{
  int a[3]; scanf("%d %d %d", &a[0], &a[1], &a[2]);
  int best = 1<<20;

  for (int i = 0; i < 3; i ++)
  {
    int now = 0;
    for (int j = 0; j < 3; j ++)
      now += a[j] * abs(i - j) * 2;
    if (now < best) best = now;
  }

  printf("%d\n", best);

  return(0);
}