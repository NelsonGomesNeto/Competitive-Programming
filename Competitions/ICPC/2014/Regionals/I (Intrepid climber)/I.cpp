#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, f;
vector<pair<int, int>> tree[maxN];
int friends[maxN];

int countFriends(int u = 0, int prv = -1)
{
  for (auto v: tree[u])
    if (v.first != prv)
      friends[u] += countFriends(v.first, u);
  return(friends[u]);
}

lli totalPath, removablePath;
void dfs(int u = 0, int prv = -1, lli path = 0)
{
  removablePath = max(removablePath, path);
  for (auto v: tree[u])
    if (v.first != prv && friends[v.first])
    {
      dfs(v.first, u, path + v.second);
      totalPath += v.second;
    }
}

int main()
{
  scanf("%d %d", &n, &f);
  for (int i = 0, u, v, c; i < n - 1; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    tree[u].push_back({v, c}), tree[v].push_back({u, c});
  }

  for (int i = 0, u; i < f; i ++)
  {
    scanf("%d", &u); u --;
    friends[u] = 1;
  }
  countFriends();
  dfs();
  printf("%lld\n", totalPath - removablePath);

  return(0);
}