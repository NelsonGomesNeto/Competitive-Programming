#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10;
int n, m;
vector<pair<int, int>> graph[maxN];

int visited[maxN];
int solve(int u) {
  visited[u] = true;

  int ans = 0;
  for (auto [v, c] : graph[u])
    if (!visited[v])
      ans = max(ans, c + solve(v));

  visited[u] = false;
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < n; ++i) graph[i].clear();

    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      --u, --v;
      graph[u].emplace_back(v, c);
      graph[v].emplace_back(u, c);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      memset(visited, false, sizeof(visited));
      ans = max(ans, solve(i));
    }
    printf("%d\n", ans);
  }
  return 0;
}
