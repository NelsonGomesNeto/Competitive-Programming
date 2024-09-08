#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e9; int n, m;
map<lli, vector<lli>> blacks;

set<lli> visited;
bool canReach(lli lox, lli hix, lli y)
{
  if (!blacks.count(y) || blacks[y].empty()) return true;

  auto &pos = blacks[y];
  auto b = upper_bound(pos.begin(), pos.end(), lox);
  if (b == pos.end() || *b > hix) return true;
  return false;
}
void dfs(lli x = 0, lli y = n)
{
  DEBUG printf("%lld %lld | %d\n", x, y, canReach(x, 2*n, y));

  set<pair<lli, lli>> q;
  q.insert({x, y});
  while (!q.empty())
  {
    x = q.begin()->first, y = q.begin()->second;
    q.erase(q.begin());

    if (blacks.count(y - 1) && !blacks[y - 1].empty())
    {
      auto &l = blacks[y - 1];
      auto toKill = upper_bound(l.begin(), l.end(), x);
      for (auto toKill = upper_bound(l.begin(), l.end(), x); toKill != l.end(); toKill++)
        if (canReach(x, (*toKill) - 1, y))
          q.insert({*toKill, y - 1});
        else
          break;
    }
    if (blacks.count(y + 1) && !blacks[y + 1].empty())
    {
      auto &r = blacks[y + 1];
      for (auto toKill = upper_bound(r.begin(), r.end(), x); toKill != r.end(); toKill++)
        if (canReach(x, (*toKill) - 1, y))
          q.insert({*toKill, y + 1});
        else
          break;
    }

    if (canReach(x, 2*n, y))
      visited.insert(y);
  }
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    blacks.clear();
    for (int i = 0; i < m; i++)
    {
      int x, y; scanf("%d %d", &x, &y);
      blacks[y].push_back(x);
    }

    for (auto &b: blacks)
      sort(b.second.begin(), b.second.end());

    visited.clear();
    dfs();
    int ans = visited.size();
    
    printf("%d\n", ans);
  }
  return 0;
}