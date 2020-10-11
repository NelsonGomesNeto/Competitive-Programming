#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
int a[maxN];
int diff[maxN];
int ans[maxN];
vector<int> pos[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++) pos[i].clear();
      for (int i = 0; i < n; i++)
      {
        scanf("%d", &a[i]); a[i]--;
        pos[a[i]].push_back(i);
      }

      for (int i = 0; i < n; i++) diff[i] = -1;
      for (int i = 0; i < n; i++)
        if (!pos[i].empty())
        {
          diff[i] = max(*pos[i].begin(), n - 1 - *pos[i].rbegin());
          for (int j = 0; j < pos[i].size() - 1; j++)
            diff[i] = max(diff[i], pos[i][j + 1] - pos[i][j] - 1);
        }

      for (int i = 0; i < n; i++) ans[i] = -1;
      for (int i = n - 1 ; i >= 0; i--) if (diff[i] != -1) ans[diff[i]] = i + 1;

      for (int i = 0; i < n; i++)
        if (ans[i] != -1)
        {
          int j = i;
          while (j + 1 < n && (ans[j + 1] >= ans[i] || ans[j + 1] == -1))
            ans[++j] = ans[i];
          i = j;
        }
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}
