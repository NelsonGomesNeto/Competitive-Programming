#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  bool levels[n]; memset(levels, false, sizeof(levels));
  for (int i = 0, l; i < 2; i ++)
  {
    scanf("%d", &l);
    for (int j = 0, a; j < l; j ++)
    {
      scanf("%d", &a);
      levels[a - 1] = true;
    }
  }

  bool can = true; for (int i = 0; i < n; i ++) if (!levels[i]) can = false;
  printf("%s\n", can ? "I become the guy." : "Oh, my keyboard!");
  return(0);
}