#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxM = 1e5, maxC = 2e5; int n, m;
vector<lli> a[maxN];
vector<int> b[maxM];
set<vector<int>> bmap;
bitset<maxC> banned[maxN];
vector<int> ans;

int main()
{
  while (~scanf("%d", &n))
  {
    ans.clear(); ans.resize(n);

    for (int i = 0; i < n; i++)
    {
      int c; scanf("%d", &c);
      a[i].clear(); a[i].resize(c);
      for (auto &aa: a[i]) scanf("%lld", &aa);
    }

    scanf("%d", &m);
    for (int i = 0; i < n; i++) banned[i] = 0;
    bmap.clear();
    for (int i = 0; i < m; i++)
    {
      b[i].clear(); b[i].resize(n);
      for (int j = 0; j < n; j++)
      {
        scanf("%d", &b[i][j]);
        b[i][j]--;
        banned[j][b[i][j]] = true;
      }
      bmap.insert(b[i]);
    }

    lli best = 0;
    for (int i = 0; i < n; i++)
    {
      vector<int> curr;
      lli build = 0;
      for (int j = 0; j < n; j++) curr.push_back(a[j].size() - 1), build += a[j].back();

      while (curr[i] >= 0 && build > best && bmap.count(curr))
      {
        build -= a[i][curr[i]];
        curr[i]--;
        if (curr[i] >= 0) build += a[i][curr[i]];
      }

      if (curr[i] >= 0)
      {
        ans = curr;
        best = build;
      }
    }

    for (int i = 0; i < m; i++)
    {
      lli build = 0;
      for (int j = 0; j < n; j++) build += a[j][b[i][j]];

      vector<int> curr = b[i];
      for (int j = 0; j < n; j++)
      {
        build -= b[i][j];

        if (curr[j] - 1 >= 0)
        {
          curr[j]--;
          build += a[j][curr[j]];
          if (build > best && !bmap.count(curr))
          {
            ans = curr;
            best = build;
          }
          build -= a[j][curr[j]];
          curr[j]++;
        }

        if (curr[j] + 1 < a[j].size())
        {
          curr[j]++;
          build += a[j][curr[j]];
          if (build > best && !bmap.count(curr))
          {
            ans = curr;
            best = build;
          }
          build -= a[j][curr[j]];
          curr[j]--;
        }

        build += b[i][j];
      }
    }

    DEBUG printf("\t%lld\n", best);
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i] + 1, i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
