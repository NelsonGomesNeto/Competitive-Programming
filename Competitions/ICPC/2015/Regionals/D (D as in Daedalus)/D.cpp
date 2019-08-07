#include <bits/stdc++.h>
using namespace std;

const int maxN = 20, maxM = 50; int n, m;
int rounds[maxM][maxN + 1];

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
    for (int j = 0; j <= n; j ++)
      scanf("%d", &rounds[i][j]);

  int ans = 0;
  for (int i = 0; i < m; i ++)
  {
    int s = 0;
    for (int j = 0; j < n; j ++) s += rounds[i][j + 1];
    if (s <= rounds[i][0]) ans -= rounds[i][1];
  }

  for (int i = 0; i < m; i ++)
  {
    int s = 0;
    for (int j = 1; j < n; j ++) s += rounds[i][j + 1];
    int c = 1;
    for (int j = 0; j < 5; j ++)
    {
      if (s + c > rounds[i][0]) break;
      c *= 10;
    }
    c /= 10;
    if (c && (s + c <= rounds[i][0])) ans += c;
  }
  printf("%d\n", ans);

  return(0);
}