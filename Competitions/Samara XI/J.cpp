#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int s, side[(int) 2e5 + 1]; memset(side, 0, sizeof(side));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &s);
    side[s] ++;
  }

  int sum = 0;
  for (int i = 0; i < 2e5 + 1; i ++) sum += side[i] / 2;
  printf("%d\n", sum / 2);
  return(0);
}