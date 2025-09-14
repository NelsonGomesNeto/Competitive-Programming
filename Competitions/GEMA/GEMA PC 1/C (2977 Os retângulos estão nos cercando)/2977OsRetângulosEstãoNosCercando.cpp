#include <bits/stdc++.h>

const int maxX = 500 + 1;
int cnt[maxX][maxX];

int main()
{
  int n;
  while (scanf("%d", &n) != EOF && n)
  {
    memset(cnt, 0, sizeof(cnt));
    for (int k = 0; k < n; k ++)
    {
      int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
      assert(a < c); assert(b < d);
      for (int i = a; i < c; i ++)
        for (int j = b; j < d; j ++)
          cnt[i][j] ++;
    }
    
    int ans = 0;
    for (int i = 0; i < maxX; i ++)
      for (int j = 0; j < maxX; j ++)
        ans += cnt[i][j] > 0;
    printf("%d\n", ans);
  }
  return 0;
}