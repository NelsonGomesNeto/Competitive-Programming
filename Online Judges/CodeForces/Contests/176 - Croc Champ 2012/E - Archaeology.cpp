#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Explanation:
First you will DFS count the time in which you've visited each vertex.
Now think this way: you have a subtree with k vertices. Sort them by visiting order.
If you went throught this path: v_1 -> v_2 -> ... -> v_(k-1) -> v_k -> v_1
You would've passed thought each edge (of the subtree) *exactly* twice.
Instead of sorting, you better store the subtree's vertices in a set<pair<int, int>>
Queries will be like:
  ?: sum / 2.
  + and -: u might end at the beginning, end or middle, but you will always do:
    total (+-)= distance(prev(u), u) + distance(u, next(u)) - distance(prev(u), next(u))
    prev and next will vary accordingly to where u is, but it's easy to add ifs for that
*/

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, logn;
vector<pair<int, lli>> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], in[maxN], t; lli dist[maxN], total;
set<pair<int, int>> subtree; // (in[u], u)
void dfs(int u, int prev)
{
  in[u] = ++ t;
  for (auto v: tree[u])
    if (v.first != prev)
    {
      level[v.first] = level[u] + 1, ancestor[v.first][0] = u, dist[v.first] = dist[u] + v.second;
      dfs(v.first, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = dist[0] = t = 0; dfs(0, -1);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1) u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logn - 1; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}
lli distance(int u, int v)
{
  return(dist[u] + dist[v] - 2*dist[LCA(u, v)]);
}

void rem(int u)
{
  set<pair<int, int>>::iterator it = subtree.find({in[u], u});
  if (it == subtree.end()) return;
  if (subtree.size() <= 2) { subtree.erase(it); total = 0; return; }
  else if (subtree.size() == 3) { subtree.erase(it); total = 2*distance(subtree.begin()->second, prev(subtree.end(), 1)->second); }
  else
  {
    if (it == subtree.begin()) total -= distance(it->second, next(subtree.begin(), 1)->second) + distance(prev(subtree.end(), 1)->second, it->second) - distance(prev(subtree.end(), 1)->second, next(subtree.begin(), 1)->second);
    else if (it == prev(subtree.end(), 1)) total -= distance(it->second, subtree.begin()->second) + distance(prev(subtree.end(), 2)->second, it->second) - distance(prev(subtree.end(), 2)->second, subtree.begin()->second);
    else total -= distance(it->second, next(it, 1)->second) + distance(prev(it, 1)->second, it->second) - distance(prev(it, 1)->second, next(it, 1)->second);
    subtree.erase(it);
  }
}

void add(int u)
{
  subtree.insert({in[u], u});
  if (subtree.size() == 1) return;
  else if (subtree.size() == 2) total = 2*distance(subtree.begin()->second, prev(subtree.end(), 1)->second);
  else
  {
    set<pair<int, int>>::iterator it = subtree.find({in[u], u});
    if (it == subtree.begin()) total += distance(it->second, next(subtree.begin(), 1)->second) + distance(prev(subtree.end(), 1)->second, it->second) - distance(prev(subtree.end(), 1)->second, next(subtree.begin(), 1)->second);
    else if (it == prev(subtree.end(), 1)) total += distance(it->second, subtree.begin()->second) + distance(prev(it, 1)->second, it->second) - distance(prev(it, 1)->second, subtree.begin()->second);
    else total += distance(it->second, next(it, 1)->second) + distance(prev(it, 1)->second, it->second) - distance(prev(it, 1)->second, next(it, 1)->second);
  }
}

int main()
{
  scanf("%d", &n); logn = ceil(log2(n));
  int u, v; lli c;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d %lld", &u, &v, &c); u --, v --;
    tree[u].push_back({v, c}); tree[v].push_back({u, c});
  }
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    char op; scanf("\n%c", &op);
    if (op == '?') printf("%lld\n", total >> 1);
    else
    {
      scanf("%d", &u); u --;
      if (op == '+') add(u); else rem(u);
    }
  }
  return(0);
}
