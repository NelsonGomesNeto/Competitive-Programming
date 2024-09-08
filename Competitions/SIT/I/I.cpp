#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 250000; int n;
pair<int, int> cards[maxN];
map<int, int> cnt[2*maxN + 1], total;
map<pair<int, int>, int> bothCnt;
set<pair<int, int>> otherTotal;

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d %d", &cards[i].first, &cards[i].second);
      if (cards[i].first > cards[i].second)
        swap(cards[i].first, cards[i].second);
    }

    sort(cards, cards+n);
    total.clear();
    bothCnt.clear();
    for (int i = 0; i <= 2*n; i++)
      cnt[i].clear();
    for (int i = 0; i < n; i++)
    {
      int a = cards[i].first, b = cards[i].second;
      auto p = make_pair(min(a, b), max(a, b));
      if (!bothCnt.count(p))
        bothCnt[p] = 0;
      bothCnt[p]++;

      if (a == b)
      {
        if (!cnt[a].count(b))
          cnt[a][b] = 0;
        cnt[a][b]++;

        if (!total.count(a))
          total[a] = 0;
        total[a]++;
      }
      else
      {
        if (!cnt[a].count(a))
          cnt[a][a] = 0;

        if (!cnt[a].count(b))
          cnt[a][b] = 0;
        cnt[a][b]++;

        if (!total.count(a))
          total[a] = 0;
        total[a]++;

        swap(a, b);

        if (!cnt[a].count(a))
          cnt[a][a] = 0;

        if (!cnt[a].count(b))
          cnt[a][b] = 0;
        cnt[a][b]++;

        if (!total.count(a))
          total[a] = 0;
        total[a]++;
      }
    }

    otherTotal.clear();
    for (int x = 1; x <= 2*n; x++)
      otherTotal.insert({total[x], x});

    int ans = 1e9;
    for (int x = 1; x <= 2*n; x++)
    {
      // x have y and x == y
      for (auto &p: cnt[x])
      {
        int curr = 0;
        if (x != p.first)
          curr = (n - total[x]) // paint first
                  + (total[x] - p.second) // paint second inside first
                  + (n - total[x]) // paint second outside first
                  - (total[p.first] - cnt[p.first][x]);
        else
          curr = 2*n - total[x] - bothCnt[make_pair(x, x)];
        // int curr = (n - total[x])
        //           + (n - total[p.first])
        //           - bothCnt[make_pair(min(x, p.first), max(x, p.first))];
        DEBUG printf("\t%d %d | %d %d | %d\n", x, p.first, total[x], p.second, curr);
        ans = min(ans, curr);

        otherTotal.erase({total[p.first], p.first});
      }

      // x doens't have y
      if (!otherTotal.empty())
        ans = min(ans, 2*n - total[x] - otherTotal.rbegin()->first);

      for (auto &p: cnt[x])
        otherTotal.insert({total[p.first], p.first});
    }

    printf("%d\n", ans);
  }
  return 0;
}