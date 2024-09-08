#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 30; int n; lli k;
lli p[maxN];
vector<lli> ps;

lli getWin(lli lo, lli hi)
{
  DEBUG printf("\t%lld %lld\n", lo, hi);
  if (lo == 1 || hi == k) return hi - lo + 1;
  if ((hi - lo + 1) & 1LL) return (hi - lo + 2) >> 1LL;
  else return (hi - lo + 1) >> 1LL;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &k);
    ps.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &p[i]);
      ps.push_back(p[i]);
    }
    sort(ps.begin(), ps.end());
    ps.resize(distance(ps.begin(), unique(ps.begin(), ps.end())));

    vector<pair<lli, lli>> blocks;
    if (ps[0] != 1)
      blocks.push_back({1, ps[0] - 1});
    for (int i = 1; i < ps.size(); i++)
      if (ps[i - 1] + 1 < ps[i])
        blocks.push_back({ps[i - 1] + 1, ps[i] - 1});
    if (ps.back() != k)
      blocks.push_back({ps.back() + 1, k});

    double ans;
    if (blocks.size() == 0)
      ans = 0;
    else if (blocks.size() == 1)
    {
      ans = (double)(blocks[0].second - blocks[0].first + 1) / k;
    }
    else
    {
      ans = 0;
      vector<lli> poll;
      for (auto &b: blocks)
      {
        poll.push_back(getWin(b.first, b.second));
        ans = max(ans, (double)(b.second - b.first + 1) / k);
      }
      sort(poll.begin(), poll.end(), greater<lli>());

      ans = max(ans, (double)(poll[0] + poll[1]) / k);
    }

    printf("Case #%d: %.15lf\n", tt, ans);
  }
  return 0;
}