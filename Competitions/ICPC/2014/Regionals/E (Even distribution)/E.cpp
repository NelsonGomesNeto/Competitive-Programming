#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4; int n, m;

int candies[maxN];
vector<int> graph[maxN];
set<int> memo[maxN];
set<int> ways;

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%d", &candies[i]);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }

  queue<pair<int, int>> q;
  for (int i = 0; i < n; i ++)
    q.push({i, candies[i]}), memo[i].insert(candies[i]), ways.insert(candies[i]);

  while (!q.empty())
  {
    int u = q.front().first, g = q.front().second; q.pop();
    for (int v: graph[u])
    {
      int newG = gcd(g, candies[v]);
      if (memo[v].count(newG)) continue;
      q.push({v, newG}), memo[v].insert(newG), ways.insert(newG);
    }
  }

  printf("%d\n", (int) ways.size());

  return(0);
}