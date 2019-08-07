#include <bits/stdc++.h>

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int has[m + 1], h = m; memset(has, 0, sizeof(has));
  int l, r;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &l, &r);
    for (int j = l; j <= r; j ++)
    {
      if (!has[j]) h --;
      has[j] = 1;
    }
  }

  printf("%d\n", h);
  for (int i = 1; i <= m; i ++)
    if (!has[i]) printf("%d ", i);

  return(0);
}
