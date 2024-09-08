#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3;
int n, m;
vector<int> graph[maxN];
int k;
struct Cond
{
  int u, d;
  void read()
  {
    scanf("%d %d", &u, &d);
    --u;
  }
};
Cond conds[maxN];

bool isBlack[maxN];

bool visited[maxN];
void paint(int start, int td)
{
  memset(visited, false, sizeof(visited));

  queue<pair<int, int>> q;
  q.push({start, 0});
  while (!q.empty())
  {
    auto [u, d] = q.front();
    q.pop();
    if (visited[u]) continue;
    visited[u] = true;

    if (d == td) continue;
    isBlack[u] = false;

    for (int v : graph[u])
      q.push({v, d + 1});
  }
}

bool isValid(int start, int td)
{
  memset(visited, false, sizeof(visited));

  queue<pair<int, int>> q;
  q.push({start, 0});
  while (!q.empty())
  {
    auto [u, d] = q.front();
    q.pop();
    if (visited[u])
      continue;
    visited[u] = true;

    if (isBlack[u])
      return d == td;

    for (int v : graph[u])
      q.push({v, d + 1});
  }
  return false;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
      graph[i].clear();
    for (int i = 0; i < m; ++i)
    {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
      conds[i].read();

    fill(isBlack, isBlack+n, true);
    for (int i = 0; i < k; ++i)
      paint(conds[i].u, conds[i].d);

    bool valid = true;
    for (int i = 0; i < k; ++i)
      valid &= isValid(conds[i].u, conds[i].d);

    if (!valid) printf("No\n");
    else
    {
      printf("Yes\n");
      for (int i = 0; i < n; ++i) printf("%d", isBlack[i]);
      printf("\n");
    }
  }
  return 0;
}
