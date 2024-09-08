#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxM = 2e5; int n, m, q;
lli ans[maxN];
vector<pair<int, lli>> graph[maxN];
unordered_map<int, lli> direct[maxN];
unordered_map<int, lli> memo[maxN];

int main() {
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase) {
    scanf("%d %d %d", &n, &m, &q);
    fill(ans, ans+n, 0);
    for (int i = 0; i < n; ++i) graph[i].clear(), direct[i].clear(), memo[i].clear();

    for (int i = 0; i < m; ++i) {
      int u, v; lli c; scanf("%d %d %lld", &u, &v, &c); --u, --v;
      graph[u].push_back({v, c}), graph[v].push_back({u, c});
      direct[u][v] = direct[v][u] = c;
    }

    for (int i = 0; i < n; ++i) sort(graph[i].begin(), graph[i].end());

    for (int qq = 0; qq < q; ++qq) {
      int u, v; scanf("%d %d", &u, &v); --u, --v;
      if (memo[u].count(v)) {
        ans[qq] = memo[u][v];
        continue;
      }
      ans[qq] = 2LL * direct[u][v];
      for (int i = 0, j = 0; i < graph[u].size() && j < graph[v].size(); ++i, ++j) {
        while (i < graph[u].size() && j < graph[v].size() && graph[u][i].first != graph[v][j].first) {
          while (i < graph[u].size() && graph[u][i].first < graph[v][j].first) ++i;
          if (i == graph[u].size()) break;
          while (j < graph[v].size() && graph[v][j].first < graph[u][i].first) ++j;
        }
        if (i < graph[u].size() && j < graph[v].size()) {
          assert(graph[u][i].first == graph[v][j].first);
          ans[qq] += min(graph[u][i].second, graph[v][j].second);
        }
      }
      memo[u][v] = memo[v][u] = ans[qq];
    }

    printf("Case #%d:", testCase);
    for (int qq = 0; qq < q; ++qq) printf(" %lld", ans[qq]);
    printf("\n");
  }
  return 0;
}
