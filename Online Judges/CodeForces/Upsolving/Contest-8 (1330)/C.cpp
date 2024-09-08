#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
lli acc[maxN + 1];
pair<int, int> l[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < m; i++)
    {
      scanf("%d", &l[i].first);
      l[i].second = i;
    }
    // sort(l, l+m);
    // reverse(l, l+m);
    for (int i = 0; i < m; i++)
      acc[i + 1] = acc[i] + l[i].first;

    vector<pair<int, int>> ans;
    if (acc[m] >= n)
    {
      ans.push_back({l[0].second, 0});
      for (int i = 1, at = 1, lol = l[0].first; i < m; i++)
      {
        lli left = acc[m] - acc[i];
        DEBUG printf("%d %d %d %lld %d\n", i, at + 1, lol + 1, left, max(at, (int)max(0LL, n - left)) + 1);
        if (lol + left < n)
        {
          ans.clear();
          break;
        }
        int pos = max(at, (int)max(0LL, n - left));
        if (pos > lol)
        {
          ans.clear();
          break;
        }
        ans.push_back({l[i].second, pos});
        at = pos + 1;
        lol = max(lol, pos + l[i].first);
        if ((i < m - 1 && at >= n) || lol > n)
        {
          ans.clear();
          break;
        }
      }
    }

    if (ans.size() < m) printf("-1\n");
    else
    {
      sort(ans.begin(), ans.end());
      for (int i = 0; i < m; i++)
        printf("%d%c", ans[i].second + 1, i < m - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
