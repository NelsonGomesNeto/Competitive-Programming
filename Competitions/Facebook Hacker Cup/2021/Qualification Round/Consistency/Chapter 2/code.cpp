#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, k;
char s[maxN + 1], ab[3];
bitset<256> visited;
vector<char> graph[256];

int change(char from, char to)
{
  if (from == to) return 0;
  queue<pair<int, int>> q;
  q.push({from, 0});
  while (!q.empty())
  {
    int u = q.front().first, d = q.front().second;
    q.pop();
    if (u == to) return d;
    if (visited[u]) continue;
    visited[u] = true;
    for (char v: graph[u])
      q.push({v, d + 1});
  }
  return 1e6;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    n = strlen(s);

    for (int i = 'A'; i <= 'Z'; i++)
      graph[i].clear();
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
      scanf(" %s", ab);
      graph[ab[0]].push_back(ab[1]);
      // graph[ab[1]].push_back(ab[0]);
    }

    int ans = 1e9;
    for (int i = 'A'; i <= 'Z'; i++)
    {
      int cost = 0;
      for (int j = 0; j < n; j++)
      {
        visited = 0;
        cost += change(s[j], i);
      }
      ans = min(ans, cost);
    }

    if (ans >= 1e6) ans = -1;
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}
