#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool lol = true;
struct TestCase {
bool stopped = false;
operator bool() { return !stopped; }

int n, m, g;
vector<vector<int>> graph;
vector<set<int>> prohibited;
vector<int> c, s, indegree;
vector<vector<int>> group;
TestCase() {
  if (lol) { lol = false; return; }
  if (scanf("%d %d %d", &n, &m, &g) == EOF) {
    stopped = true;
    return;
  }

  graph.resize(n), indegree.resize(n);
  prohibited.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    graph[u].push_back(v), ++indegree[u];
    prohibited[u].insert(v);
  }

  c.resize(n);
  group.resize(g);
  for (int i = 0; i < n; ++i) {
    int& cc = c[i];
    scanf("%d", &cc);
    --cc;
    group[cc].push_back(i);
  }
  s.resize(n);
  for (int& ss : s) scanf("%d", &ss);
}

vector<vector<int>> memo;
int Solve(int i, int prv) {
  if (i == -1) return 0;
  int& ans = memo[i][prv];
  if (ans != -1) return ans;

  ans = 0;
  for (int p : group[i])
    if (!prohibited[p].count(prv))
      ans = max(ans, Solve(i - 1, p) + s[p]);
  return ans;
}

void Run() {
  memo.resize(g, vector<int>(n + 1, -1));
  int ans = Solve(g - 1, n);
  printf("%d\n", ans);
}
};
TestCase test_case;

int main() {
  while (test_case = TestCase()) {
    test_case.Run();
  }
  return 0;
}
