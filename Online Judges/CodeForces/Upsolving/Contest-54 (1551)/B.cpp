#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
int a[maxN];
vector<int> pos[maxN + 1];
map<pair<int, int>, queue<int>> aux;

int ans[maxN];
bool can(int x)
{
  aux.clear();
  for (int i = 0; i <= n; i++)
  {
    ans[i] = 0;
    if (!pos[i].empty())
    {
      auto p = make_pair(-pos[i].size(), i);
      while (!aux[p].empty()) aux[p].pop();
      for (int j: pos[i]) aux[p].push(j);
    }
  }

  for (int color = 1; color <= k; color++)
  {
    int xx = 0;
    list<pair<int, int>> toRemove;
    for (auto &p: aux)
    {
      if (xx == x) break;
      ans[p.second.front()] = color;
      p.second.pop();
      if (p.second.empty())
        toRemove.push_back(p.first);
      xx++;
    }
    if (xx != x) return false;
    for (auto p: toRemove) aux.erase(p);
  }
  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i <= n; i++) pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }

    int lo = 0, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }
    can(lo);

    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
