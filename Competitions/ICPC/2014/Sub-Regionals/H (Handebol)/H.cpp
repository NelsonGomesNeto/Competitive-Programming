#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int ans = 0;
  for (int i = 0; i < n; i ++)
  {
    bool all = true;
    for (int j = 0, a; j < m; j ++)
    {
      scanf("%d", &a);
      if (!a) all = false;
    }
    if (all) ans ++;
  }
  printf("%d\n", ans);
  return(0);
}