#include <bits/stdc++.h>
using namespace std;

vector<int> bottomUp(int m, int n, int t)
{
  int best[t + 1][2]; // [0] == h, [1] == t
  memset(best, 0, sizeof(best));
  for (int i = 0; i <= t; i ++)
  {
    if (i < m)
    {
      best[i][0] = 0; best[i][1] = t;
    }
    else if (i >= m && i < n)
    {
      best[i][0] = best[i - m][0] + 1;
      best[i][1] = best[i - m][1] - m;
    }
    else if (i >= n && i >= n)
    {
      if (best[i - m][1] - m > best[i - n][1] - n)
        best[i][0] = best[i - n][0] + 1;
      else if (best[i - m][1] - m < best[i - n][1] - n)
        best[i][0] = best[i - m][0] + 1;
      else
        best[i][0] = max(best[i - m][0], best[i - n][0]) + 1;
      best[i][1] = min(best[i - m][1] - m, best[i - n][1] - n);
    }
  }
  vector<int> ans = {best[t][1], best[t][0]};
  return(ans);
}

int main()
{
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
  {
    vector<int> ans = bottomUp(min(m, n), max(m, n), t);

    printf("%d", ans[1]);
    if (ans[0] > 0)
      printf(" %d", ans[0]);
    printf("\n");
  }
  return(0);
}